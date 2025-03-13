// Fill out your copyright notice in the Description page of Project Settings.


#include "Word/Component/SteeringBehavior/Arrival.h"

#include "Word/Component/SteeringBehavior/Seek.h"
#include "Word/Component/SteeringBehavior/SteeringComponent.h"

void UArrival::ExecuteBehavior(ANPlayerCharacter* NPC, FVector TargetLocation) {
	FVector CurrentPosition = NPC->GetActorLocation();
	float DistanceToTarget = FVector::Dist(CurrentPosition, TargetLocation);
	float SlowingDistance = 200.0f;
	
	if (DistanceToTarget > SlowingDistance) {
		NPC->SeekComp->ExecuteBehavior(NPC, TargetLocation);
	} else {
		float RampedSpeed = NPC->SteeringComp->MaxSpeed * (DistanceToTarget / SlowingDistance);
		float ClippedSpeed = FMath::Min(RampedSpeed, NPC->SteeringComp->MaxSpeed);

		FVector DesiredVelocity = (TargetLocation - CurrentPosition).GetSafeNormal() * ClippedSpeed;

		float SpeedFactor = ClippedSpeed / NPC->SteeringComp->MaxSpeed;
		FVector Steering = NPC->SteeringComp->CalculateSteeringForce(NPC, DesiredVelocity);

		FVector Acceleration = Steering / NPC->SteeringComp->Mass;
		FVector NewVelocity = NPC->SteeringComp->Velocity + Acceleration;
		NewVelocity = NewVelocity.GetClampedToMaxSize(NPC->SteeringComp->MaxSpeed);
		NPC->SteeringComp->Velocity = NewVelocity;
	
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
