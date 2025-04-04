// Fill out your copyright notice in the Description page of Project Settings.


#include "ModifyLandState.h"
#include "MainCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UModifyLandState::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!IsValid(Cast<AMainCharacter>(MeshComp->GetOwner()))) return;

	AMainCharacter* MyCharacter = Cast<AMainCharacter>(MeshComp->GetOwner());
	if (MyCharacter)
	{
		MyCharacter->GetCharacterMovement()->BrakingDecelerationWalking = MyCharacter->GetCharacterMovement()->MaxWalkSpeed * 5.0f;
		MyCharacter->GetCharacterMovement()->GroundFriction = 10.0f;
	}
}
