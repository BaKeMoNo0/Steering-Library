// Fill out your copyright notice in the Description page of Project Settings.


#include "Word/Component/ChickenHandlerComponent.h"

#include "Word/Component/PathFindingManager.h"


UChickenHandlerComponent::UChickenHandlerComponent(){}


void UChickenHandlerComponent::BeginPlay() {
	Super::BeginPlay();
	OwnerCharacter = Cast<ANPCCharacter>(GetOwner());
}


void UChickenHandlerComponent::PickupChicken(ANPCCharacter* Chicken) {
	if (!Chicken) return;

	Chicken->SetActorEnableCollision(false);
	Chicken->GetMesh()->SetSimulatePhysics(false);

	Chicken->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("ChickenSocket"));
	OwnerCharacter->PathFindingManager->ChickensTargets.Remove(Chicken);
}

