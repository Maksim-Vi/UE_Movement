// Fill out your copyright notice in the Description page of Project Settings.


#include "SprintTrigger.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

// ETriggerState USprintTrigger::UpdateState(
// 	const UEnhancedPlayerInput* PlayerInput,
// 	FInputActionValue ModifiedValue, float DeltaTim)
// {
// 	UE_LOG(LogTemp, Warning, TEXT("click sprint"));
//
// 	if (PlayerInput)
// 	{
// 		UE_LOG(LogTemp, Log, TEXT("PlayerInput is valid."));
// 	}
// 	else
// 	{
// 		UE_LOG(LogTemp, Warning, TEXT("PlayerInput is NULL!"));
// 	}
//
// 	//if (!MoveAction || !SprintAction) return ETriggerState::None;
//
// 	FVector2d MoveValue = PlayerInput->GetActionValue(MoveAction).Get<FVector2d>();
// 	bool bIsSprinting = PlayerInput->GetActionValue(SprintAction).Get<bool>();
//
// 	UE_LOG(LogTemp, Warning, TEXT("bIsSprinting: %s"), bIsSprinting ? TEXT("true") : TEXT("false"));
// 	
// 	if (MoveValue.Size() > 0.0f && bIsSprinting)
// 	{
// 		return ETriggerState::Triggered;
// 	}
//
// 	return ETriggerState();
// }

ETriggerState USprintTrigger::UpdateState(const UEnhancedPlayerInput* PlayerInput,
	FInputActionValue ModifiedValue, float DeltaTime)
{
	UE_LOG(LogTemp, Warning, TEXT("UpdateState_Implementation click sprint"));

	if (!MoveAction || !SprintAction) return ETriggerState::None;

	FVector2d MoveValue = PlayerInput->GetActionValue(MoveAction).Get<FVector2d>();
	
	FInputActionValue SprintValue = PlayerInput->GetActionValue(SprintAction);
	
	bool bIsSprint = SprintValue.Get<bool>();

	UE_LOG(LogTemp, Warning, TEXT("UpdateState_Implementation bIsSprinting: %s"), bIsSprint ? TEXT("true") : TEXT("false"));
	
	if (MoveValue.Size() > 0.0f && bIsSprint)
	{
		return ETriggerState::Triggered;
	}

	return ETriggerState();
}
	
