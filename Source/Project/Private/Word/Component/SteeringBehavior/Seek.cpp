// Fill out your copyright notice in the Description page of Project Settings.


#include "Word/Component/SteeringBehavior/Seek.h"

#include "GameFramework/Character.h"
#include "Word/Component/SteeringBehavior/SteeringComponent.h"


void USeek::ExecuteBehavior(ACharacter* NPC, FVector TargetLocation, USteeringComponent* SteeringComp) {
	if (!NPC) return;

	FVector CurrentPosition = NPC->GetActorLocation();
	FVector DesiredVelocity = (TargetLocation - CurrentPosition).GetSafeNormal() * MaxSpeed;
	FVector Steering = SteeringComp->CalculateSteeringForce(NPC, DesiredVelocity);
	SteeringComp->MoveWithSteering(NPC, Steering);
}

