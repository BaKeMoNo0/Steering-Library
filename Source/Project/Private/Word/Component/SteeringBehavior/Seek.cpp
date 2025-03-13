// Fill out your copyright notice in the Description page of Project Settings.


#include "Word/Component/SteeringBehavior/Seek.h"

#include "Word/Component/SteeringBehavior/SteeringComponent.h"


void USeek::ExecuteBehavior(ANPlayerCharacter* NPC, FVector TargetLocation) {
	if (!NPC) return;

	FVector CurrentPosition = NPC->GetActorLocation();
	FVector DesiredVelocity = (TargetLocation - CurrentPosition).GetSafeNormal() * MaxSpeed;
	FVector Steering = NPC->SteeringComp->CalculateSteeringForce(NPC,DesiredVelocity);
	NPC->SteeringComp->MoveWithSteering(NPC, Steering);
}
