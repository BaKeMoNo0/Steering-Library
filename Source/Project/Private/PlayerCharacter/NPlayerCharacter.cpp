// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter/NPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "PlayerCharacter/PlayerCharacter.h"


ANPlayerCharacter::ANPlayerCharacter() {
 	PrimaryActorTick.bCanEverTick = true;
	MaxSpeed = 600.0f;
	MaxForce = 200.0f;
	Mass = 1.0f;
	CurrentBehavior = Walk;
}


void ANPlayerCharacter::BeginPlay() {
	Super::BeginPlay();
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}


void ANPlayerCharacter::SetBehavior(UEBehaviorType NewBehavior){
	CurrentBehavior = NewBehavior;
}


void ANPlayerCharacter::ExecuteCurrentBehavior(FVector TargetLocation) {
	switch (CurrentBehavior) {
	case Walk:
		AddMovementInput(GetActorForwardVector(), 1.0f);
		break;
	case Seek:
		SeekBehavior(TargetLocation);
		break;
	case Flee:
		FleeBehavior(TargetLocation);
		break;
	case Pursuit:
		PursuitBehavior(TargetLocation);
		break;
	case Evade:
		EvadeBehavior(TargetLocation);
		break;
	case Arrival:
		ArriveBehavior(TargetLocation);
		break;
	default:
		break;
	}
}


FVector ANPlayerCharacter::CalculateSteeringForce(const FVector& DesiredVelocity) const {
	FVector CurrentVelocity = GetCharacterMovement()->Velocity;
	FVector Steering = DesiredVelocity - CurrentVelocity;
	return Steering.GetClampedToMaxSize(MaxForce);
}


void ANPlayerCharacter::MoveWithSteering(const FVector& Steering) {
	FVector CurrentVelocity = GetCharacterMovement()->Velocity;
	FVector Acceleration = Steering / Mass;
	FVector NewVelocity = CurrentVelocity + Acceleration;
	NewVelocity = NewVelocity.GetClampedToMaxSize(MaxSpeed);
	
	FVector NewForward = NewVelocity.GetSafeNormal();
	AddMovementInput(NewForward, 1.0f);

	if (!NewVelocity.IsNearlyZero()) {
		FVector ApproximateUp = FVector::UpVector;
		FVector NewRight = ApproximateUp.Cross(NewForward).GetSafeNormal(); // Calcul Axe Y
		FVector NewUp = NewForward.Cross(NewRight).GetSafeNormal(); // Calcul Axe Z
		FMatrix NewRotationMatrix(NewForward, NewRight, NewUp, FVector::ZeroVector);
		FRotator NewRotation = NewRotationMatrix.Rotator();
		SetActorRotation(NewRotation);
	}
}


void ANPlayerCharacter::SeekBehavior(const FVector& Target) {
	FVector CurrentPosition = GetActorLocation();
	FVector DesiredVelocity = (Target - CurrentPosition).GetSafeNormal() * MaxSpeed;
	FVector Steering = CalculateSteeringForce(DesiredVelocity);
	MoveWithSteering(Steering);
}


void ANPlayerCharacter::FleeBehavior(const FVector& Target) {
	FVector CurrentPosition = GetActorLocation();
	FVector DesiredVelocity = (CurrentPosition - Target).GetSafeNormal() * MaxSpeed;
	FVector Steering = CalculateSteeringForce(DesiredVelocity);
	MoveWithSteering(Steering);
}


void ANPlayerCharacter::PursuitBehavior(const FVector& Target) {
	FVector CurrentPosition = GetActorLocation();
	FVector TargetVelocity = PlayerPawn->GetVelocity();
	float DistanceToTarget = FVector::Dist(CurrentPosition, Target);

	FVector ToTarget = (Target - CurrentPosition).GetSafeNormal();
	float Alignment = FVector::DotProduct(ToTarget, TargetVelocity.GetSafeNormal());

	float c = FMath::Lerp(0.3f, 1.0f, 1.0f - (Alignment * 0.5f));

	float RelativeSpeed = (TargetVelocity - GetCharacterMovement()->Velocity).Size();
    float PredictionTime = (RelativeSpeed > 0) ? (DistanceToTarget / RelativeSpeed) * c : 0.5f;
    PredictionTime = FMath::Clamp(PredictionTime, 0.1f, 2.5f);
    FVector PredictedTarget = Target + TargetVelocity * PredictionTime;

	SeekBehavior(PredictedTarget);
}


void ANPlayerCharacter::EvadeBehavior(const FVector& Target) {
	FVector CurrentPosition = GetActorLocation();
	FVector TargetVelocity = PlayerPawn->GetVelocity();
	float DistanceToTarget = FVector::Dist(CurrentPosition, Target);

	FVector ToTarget = (Target - CurrentPosition).GetSafeNormal();
	float Alignment = FVector::DotProduct(ToTarget, TargetVelocity.GetSafeNormal());

	float c = FMath::Lerp(0.3f, 1.0f, 1.0f - (Alignment * 0.5f));
	
	float RelativeSpeed = (TargetVelocity - GetCharacterMovement()->Velocity).Size();
	float PredictionTime = (RelativeSpeed > 0) ? (DistanceToTarget / RelativeSpeed) * c : 0.3f;
	PredictionTime = FMath::Clamp(PredictionTime, 0.1f, 2.5f);
	FVector PredictedTarget = Target + TargetVelocity * PredictionTime;

	FleeBehavior(PredictedTarget);
}


void ANPlayerCharacter::ArriveBehavior(const FVector& Target) {
	FVector CurrentPosition = GetActorLocation();
	float DistanceToTarget = FVector::Dist(CurrentPosition, Target);
	float SlowingDistance = 600.0f;


	if (DistanceToTarget > SlowingDistance) {
		SeekBehavior(Target);
	} else {
		float RampedSpeed = MaxSpeed * (DistanceToTarget / SlowingDistance);
		float ClippedSpeed = FMath::Min(RampedSpeed, MaxSpeed);

		FVector DesiredVelocity = (Target - CurrentPosition).GetSafeNormal() * ClippedSpeed;

		float SpeedFactor = ClippedSpeed / MaxSpeed;
		FVector Steering = CalculateSteeringForce(DesiredVelocity);

		FVector CurrentVelocity = GetCharacterMovement()->Velocity;
		FVector Acceleration = Steering / Mass;
		FVector NewVelocity = CurrentVelocity + Acceleration;
		NewVelocity = NewVelocity.GetClampedToMaxSize(MaxSpeed);
	
		FVector NewForward = NewVelocity.GetSafeNormal();
		AddMovementInput(NewForward, SpeedFactor);

		if (!NewVelocity.IsNearlyZero()) {
			FVector ApproximateUp = FVector::UpVector;
			FVector NewRight = ApproximateUp.Cross(NewForward).GetSafeNormal(); // Calcul Axe Y
			FVector NewUp = NewForward.Cross(NewRight).GetSafeNormal(); // Calcul Axe Z
			FMatrix NewRotationMatrix(NewForward, NewRight, NewUp, FVector::ZeroVector);
			FRotator NewRotation = NewRotationMatrix.Rotator();
			SetActorRotation(NewRotation);
		}
	}
}



void ANPlayerCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (PlayerPawn) {
		FVector TargetLocation = PlayerPawn->GetActorLocation();
		ExecuteCurrentBehavior(TargetLocation);
	}
}
