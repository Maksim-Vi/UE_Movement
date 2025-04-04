// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAnimInstance.h"
#include "MainCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UMainAnimInstance::NativeInitializeAnimation()
{
	MainCharacter = Cast<AMainCharacter>(TryGetPawnOwner());
	CharacterRotationYaw = 0;
	LastCharacterRotationYaw = 0;
	RootRotationYaw = 0;
}

void UMainAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (MainCharacter != nullptr)
	{
		FVector Velocity =  MainCharacter->GetVelocity();
		Velocity.Z = 0;

		Speed = Velocity.Size();
		bIsAccelerating = MainCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.0f;
		bIsInAir = MainCharacter->GetCharacterMovement()->IsFalling();

		FRotator BaseAimRotation = MainCharacter->GetBaseAimRotation();
		FRotator MoveRotation = UKismetMathLibrary::MakeRotFromX(MainCharacter->GetVelocity());
		MovementYawDelta = UKismetMathLibrary::NormalizedDeltaRotator(MoveRotation, BaseAimRotation).Yaw;

		if (MainCharacter->GetVelocity().Size() > 0.0f)
		{
			LastMovementYawDelta = MovementYawDelta;
		}
		
		//Turn-in place
		if (Speed > 0.0f || bIsInAir)
		{
			RootRotationYaw = 0;
			CharacterRotationYaw = MainCharacter->GetActorRotation().Yaw;
			LastCharacterRotationYaw = CharacterRotationYaw;
			LastTurningCurve = 0;
			TurningCurve = 0;
		}
		else
		{
			LastCharacterRotationYaw = CharacterRotationYaw;
			CharacterRotationYaw = MainCharacter->GetActorRotation().Yaw;
			const float CharacterRotationYawDelta = CharacterRotationYaw - LastCharacterRotationYaw;
			RootRotationYaw = UKismetMathLibrary::NormalizeAxis(RootRotationYaw - CharacterRotationYawDelta);

			//UE_LOG(LogTemp, Warning, TEXT("RootRotationYaw: %f"), RootRotationYaw);
			//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("RootRotationYaw: %f"), RootRotationYaw));

			IsTurning = GetCurveValue(FName(TEXT("isTurning")));

			if (IsTurning > 0)
			{
				LastTurningCurve = TurningCurve;
				TurningCurve = GetCurveValue(FName(TEXT("Turning")));

				const float TurnCurveDelta = TurningCurve - LastTurningCurve;
		
				RootRotationYaw > 0
					? RootRotationYaw -= TurnCurveDelta
					: RootRotationYaw += TurnCurveDelta;

				if (FMath::Abs(RootRotationYaw) > 90.0f)
				{
					const float AdditionalRootRotationYaw = FMath::Abs(RootRotationYaw) - 90.0f;
					RootRotationYaw > 0
						? RootRotationYaw -= AdditionalRootRotationYaw
						: RootRotationYaw += AdditionalRootRotationYaw;
				}
			}
		}
		
		CalcLeanYawDelta(DeltaSeconds);

		bShouldTurnHits = FMath::Abs(MovementYawDelta) < 55.0f && bIsAccelerating;
		bShouldRunningBackward = FMath::Abs(MovementYawDelta) > 125.0f && bIsAccelerating;
	}
}

void UMainAnimInstance::CalcLeanYawDelta(float DeltaSeconds)
{
	LeanLastCharacterRotation = LeanCharacterRotation;

	LeanCharacterRotation = MainCharacter->GetActorRotation();

	const float LeanTarget = UKismetMathLibrary::NormalizedDeltaRotator(LeanCharacterRotation, LeanLastCharacterRotation).Yaw / DeltaSeconds;
	LeanYawDelta = FMath::Clamp(FMath::FInterpTo(LeanYawDelta, LeanTarget, DeltaSeconds, 6.0f), -90.0f, 90.0f);
}
