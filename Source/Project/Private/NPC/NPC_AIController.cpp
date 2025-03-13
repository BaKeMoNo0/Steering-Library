// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/NPC_AIController.h"

#include "NPC/NPCCharacter.h"
#include "Word/Component/SteeringBehavior/Seek.h"

void ANPC_AIController::BeginPlay() {
	Super::BeginPlay();
}

void ANPC_AIController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);
	OwnerCharacter = Cast<ANPCCharacter>(InPawn);
}

void ANPC_AIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (OwnerCharacter && OwnerCharacter->bIsMoving && !CurrentTargetLocation.IsNearlyZero()) {
		MoveToTarget(CurrentTargetLocation);
		float Distance = FVector::Dist(OwnerCharacter->GetActorLocation(), CurrentTargetLocation);
		if (Distance < 150.0f) { 
			OwnerCharacter->OnReachDestination();
		}
	}
}


void ANPC_AIController::MoveToTarget(FVector TargetLocation) {
	CurrentTargetLocation = TargetLocation;
	if (OwnerCharacter->SeekComp && OwnerCharacter->SteeringComp) {
		OwnerCharacter->SeekComp->ExecuteBehavior(OwnerCharacter, TargetLocation, OwnerCharacter->SteeringComp);
	}
}
