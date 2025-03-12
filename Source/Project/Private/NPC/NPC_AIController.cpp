// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/NPC_AIController.h"

#include "NPC/NPCCharacter.h"

void ANPC_AIController::BeginPlay() {
	Super::BeginPlay();
}

void ANPC_AIController::MoveToTarget(FVector TargetLocation) {
	MoveToLocation(TargetLocation);
}

void ANPC_AIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) {
	Super::OnMoveCompleted(RequestID, Result);

	ANPCCharacter* NPC = Cast<ANPCCharacter>(GetPawn());
	if (NPC) NPC->OnReachDestination();
}