// Fill out your copyright notice in the Description page of Project Settings.


#include "Word/Component/SteeringBehavior/Arrival.h"

#include "GameFramework/Character.h"
#include "Word/Component/SteeringBehavior/Seek.h"
#include "Word/Component/SteeringBehavior/SteeringComponent.h"

void UArrival::ExecuteBehavior(ACharacter* NPC, FVector TargetLocation, USteeringComponent* SteeringComp, USeek* SeekComp) {
	
	FVector CurrentPosition = NPC->GetActorLocation();
	float DistanceToTarget = FVector::Dist(CurrentPosition, TargetLocation);
	float SlowingDistance = 200.0f;
	
	if (DistanceToTarget > SlowingDistance) {
		SeekComp->ExecuteBehavior(NPC, TargetLocation, SteeringComp);
	} else {
		float RampedSpeed = SteeringComp->MaxSpeed * (DistanceToTarget / SlowingDistance);
		float ClippedSpeed = FMath::Min(RampedSpeed, SteeringComp->MaxSpeed);

		FVector DesiredVelocity = (TargetLocation - CurrentPosition).GetSafeNormal() * ClippedSpeed;

		float SpeedFactor = ClippedSpeed / SteeringComp->MaxSpeed;
		FVector Steering = SteeringComp->CalculateSteeringForce(NPC, DesiredVelocity);

		FVector Acceleration = Steering / SteeringComp->Mass;
		FVector NewVelocity = SteeringComp->Velocity + Acceleration;
		NewVelocity = NewVelocity.GetClampedToMaxSize(SteeringComp->MaxSpeed);
		SteeringComp->Velocity = NewVelocity;
	
		FVector NewForward = NewVelocity.GetSafeNormal();
		NPC->AddMovementInput(NewForward, SpeedFactor);

		if (!NewVelocity.IsNearlyZero()) {
			FRotator NewRotation = NewVelocity.Rotation();
			NewRotation.Pitch = 0;
			NewRotation.Roll = 0;
			NPC->SetActorRotation(NewRotation);
		}
	}
}
