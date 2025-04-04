// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class LOCOMOTIONTUTORIAL_API UMainAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	void CalcLeanYawDelta(float DeltaSeconds);

private:
	class AMainCharacter* MainCharacter = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	bool bIsAccelerating;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	bool bIsInAir;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MovementYawDelta;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float LastMovementYawDelta;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Turn-in Place", meta = (AllowPrivateAccess = "true"))
	float RootRotationYaw;

	float CharacterRotationYaw;
	float LastCharacterRotationYaw;

	float IsTurning;
	float TurningCurve;
	float LastTurningCurve;

	//Lean
	FRotator LeanCharacterRotation;
	FRotator LeanLastCharacterRotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Lean Delta", meta = (AllowPrivateAccess = "true"))
	float LeanYawDelta;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Turn Hits", meta = (AllowPrivateAccess = "true"))
	bool bShouldTurnHits;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Turn Hits", meta = (AllowPrivateAccess = "true"))
	bool bShouldRunningBackward;
};
