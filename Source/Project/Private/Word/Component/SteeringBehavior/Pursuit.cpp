// Fill out your copyright notice in the Description page of Project Settings.


#include "Word/Component/SteeringBehavior/Pursuit.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Word/Component/SteeringBehavior/Seek.h"


void UPursuit::ExecuteBehavior(ACharacter* NPC, FVector TargetLocation, ACharacter* Player, USeek* SeekComp, USteeringComponent* SteeringComp) {
	if (!NPC) return;
	FVector CurrentPosition = NPC->GetActorLocation();
	FVector TargetVelocity = Player->GetVelocity();
	float DistanceToTarget = FVector::Dist(CurrentPosition, TargetLocation);

	FVector ToTarget = (TargetLocation - CurrentPosition).GetSafeNormal();
	float Alignment = FVector::DotProduct(ToTarget, TargetVelocity.GetSafeNormal());

	float c = FMath::Lerp(0.3f, 1.0f, 1.0f - (Alignment * 0.5f));

	float RelativeSpeed = (TargetVelocity - NPC->GetCharacterMovement()->Velocity).Size();
	float PredictionTime = (RelativeSpeed > 0) ? (DistanceToTarget / RelativeSpeed) * c : 0.5f;
	PredictionTime = FMath::Clamp(PredictionTime, 0.1f, 2.5f);
	FVector PredictedTarget = Player->GetActorLocation() + TargetVelocity * PredictionTime;

	SeekComp->ExecuteBehavior(NPC, PredictedTarget, SteeringComp);
}
