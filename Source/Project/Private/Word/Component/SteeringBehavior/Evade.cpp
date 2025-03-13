// Fill out your copyright notice in the Description page of Project Settings.


#include "Word/Component/SteeringBehavior/Evade.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Word/Component/SteeringBehavior/Flee.h"


void UEvade::ExecuteBehavior(ACharacter* NPC, FVector TargetLocation, ACharacter* Player, UFlee* FleeComp, USteeringComponent* SteeringComp) {
	FVector CurrentPosition = NPC->GetActorLocation();
	FVector TargetVelocity = Player->GetVelocity();
	float DistanceToTarget = FVector::Dist(CurrentPosition, TargetLocation);

	FVector ToTarget = (TargetLocation - CurrentPosition).GetSafeNormal();
	float Alignment = FVector::DotProduct(ToTarget, TargetVelocity.GetSafeNormal());

	float c = FMath::Lerp(0.3f, 1.0f, 1.0f - (Alignment * 0.5f));
	
	float RelativeSpeed = (TargetVelocity - NPC->GetCharacterMovement()->Velocity).Size();
	float PredictionTime = (RelativeSpeed > 0) ? (DistanceToTarget / RelativeSpeed) * c : 0.3f;
	PredictionTime = FMath::Clamp(PredictionTime, 0.1f, 2.5f);
	FVector PredictedTarget = TargetLocation + TargetVelocity * PredictionTime;

	FleeComp->ExecuteBehavior(NPC, PredictedTarget, SteeringComp);
}
