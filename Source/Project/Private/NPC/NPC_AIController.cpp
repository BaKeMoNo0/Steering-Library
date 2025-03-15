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
	if (!OwnerCharacter->bGoParking && OwnerCharacter->SeekComp && OwnerCharacter->SteeringComp) {
		OwnerCharacter->SeekComp->ExecuteBehavior(OwnerCharacter, TargetLocation, OwnerCharacter->SteeringComp);
	} else {
		OwnerCharacter->ArrivalComp->ExecuteBehavior(OwnerCharacter, TargetLocation, OwnerCharacter->SteeringComp, OwnerCharacter->SeekComp);
	}
}


void ANPC_AIController::CheckDistanceToTarget() {
	if (OwnerCharacter && !CurrentTargetLocation.IsNearlyZero()) {
		for (ANPCCharacter* OtherRescuer : OwnerCharacter->PathFindingManager->Farmers) {
			if (OtherRescuer != OwnerCharacter && FVector::Dist(OwnerCharacter->GetActorLocation(), OtherRescuer->GetActorLocation()) < 50.f) {
				FVector AvoidanceVector = OwnerCharacter->GetActorLocation() - OtherRescuer->GetActorLocation();
				AvoidanceVector.Normalize();
				OwnerCharacter->AddMovementInput(AvoidanceVector * 100.0f);
			}
		}
		
		float Distance = FVector::Dist(OwnerCharacter->GetActorLocation(), CurrentTargetLocation);
		if (OwnerCharacter->bGoParking || Distance < 100.f) {
			GetWorldTimerManager().ClearTimer(DistanceCheckTimer);
		}
		if (Distance < 400.0f) {
			if (OwnerCharacter->bIsLastIntersection && OwnerCharacter->bHasChicken) {
				OwnerCharacter->ChickenHandler->DropChicken(OwnerCharacter->PathFindingManager->ChickenTarget);
				OwnerCharacter->PathFindingManager->CalculatePath();
			}
			else if (OwnerCharacter->bIsLastIntersection && !OwnerCharacter->bHasChicken && OwnerCharacter->PathFindingManager->ChickenTarget) {
				OwnerCharacter->ChickenHandler->PickupChicken(OwnerCharacter->PathFindingManager->ChickenTarget);
				OwnerCharacter->PathFindingManager->CalculatePath();
			}
			else {
				OwnerCharacter->OnReachDestination();
			}
		}
	}
}