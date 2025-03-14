// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/NPC_AIController.h"

#include "NPC/NPCCharacter.h"
#include "Word/Component/ChickenHandlerComponent.h"
#include "Word/Component/PathFindingManager.h"
#include "Word/Component/SteeringBehavior/Arrival.h"
#include "Word/Component/SteeringBehavior/Seek.h"

void ANPC_AIController::BeginPlay() {
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(DistanceCheckTimer, this, &ANPC_AIController::CheckDistanceToTarget, 0.2f, true);
}

void ANPC_AIController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);
	OwnerCharacter = Cast<ANPCCharacter>(InPawn);
}

void ANPC_AIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (OwnerCharacter && !CurrentTargetLocation.IsNearlyZero()) {
		MoveToTarget(CurrentTargetLocation);
	}
}


void ANPC_AIController::MoveToTarget(FVector TargetLocation) {
	CurrentTargetLocation = TargetLocation;
	if (OwnerCharacter->SeekComp && OwnerCharacter->SteeringComp) {
		OwnerCharacter->SeekComp->ExecuteBehavior(OwnerCharacter, TargetLocation, OwnerCharacter->SteeringComp);
	}
}


void ANPC_AIController::CheckDistanceToTarget() {
	if (OwnerCharacter && !CurrentTargetLocation.IsNearlyZero()) {
		float Distance = FVector::Dist(OwnerCharacter->GetActorLocation(), CurrentTargetLocation);
		if (Distance < 400.0f) { 
			if (OwnerCharacter->bIsLastIntersection) {
				OwnerCharacter->ChickenHandler->PickupChicken(OwnerCharacter->PathFindingManager->ChickenTarget);
				OwnerCharacter->PathFindingManager->RecalculatePath();
			} 
			else {
				OwnerCharacter->OnReachDestination();
			}
		}
	}
}