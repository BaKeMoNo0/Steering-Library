// Fill out your copyright notice in the Description page of Project Settings.


#include "Word/Component/SteeringBehavior/Flee.h"

#include "GameFramework/Character.h"
#include "Word/Component/SteeringBehavior/SteeringComponent.h"


void UFlee::ExecuteBehavior(ACharacter* NPC, FVector TargetLocation, USteeringComponent* SteeringComp) {
	if (!NPC) return;

	FVector CurrentPosition = NPC->GetActorLocation();
	FVector DesiredVelocity = (CurrentPosition - TargetLocation).GetSafeNormal() * MaxSpeed;
	FVector Steering = SteeringComp->CalculateSteeringForce(NPC, DesiredVelocity);
	SteeringComp->MoveWithSteering(NPC, Steering);
}
