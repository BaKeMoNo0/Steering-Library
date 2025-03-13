// Fill out your copyright notice in the Description page of Project Settings.


#include "Word/Component/SteeringBehavior/SteeringComponent.h"

#include "GameFramework/CharacterMovementComponent.h"

FVector USteeringComponent::CalculateSteeringForce(ANPlayerCharacter* NPC, const FVector& DesiredVelocity) {
	if (Velocity == FVector::ZeroVector) Velocity = NPC->GetCharacterMovement()->Velocity;
	FVector CurrentVelocity = Velocity;
	FVector Steering = DesiredVelocity - CurrentVelocity;
	return Steering.GetClampedToMaxSize(MaxForce);
}


void USteeringComponent::MoveWithSteering(ANPlayerCharacter* NPC, const FVector& Steering) {
	FVector Acceleration = Steering / Mass;
	FVector NewVelocity = Velocity + Acceleration;
	NewVelocity = NewVelocity.GetClampedToMaxSize(MaxSpeed);
	Velocity = NewVelocity;
	FVector NewForward = NewVelocity.GetSafeNormal();
	NPC->AddMovementInput(NewForward, 1.0f);

	if (!NewVelocity.IsNearlyZero()) {
		FRotator NewRotation = NewVelocity.Rotation();
		NewRotation.Pitch = 0;
		NewRotation.Roll = 0;
		NPC->SetActorRotation(NewRotation);
	}
}

