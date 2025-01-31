// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter/NPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ANPlayerCharacter::ANPlayerCharacter() {
 	PrimaryActorTick.bCanEverTick = true;
	MaxSpeed = 600.0f;
	MaxForce = 250.0f;
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
		SeekBehavior(TargetLocation, 9.0f, 10.0f);
		break;
	case Flee:
		FleeBehavior(TargetLocation, 11.0f, 12.0f);
		break;
	case Pursuit:
		PursuitBehavior(TargetLocation);
		break;
	case Evade:
		EvadeBehavior(TargetLocation);
		break;
	default:
		break;
	}
}




void ANPlayerCharacter::MoveWithSteering(const FVector& Steering, const float InterpeSpeedRotation)
{
	FVector CurrentVelocity = GetCharacterMovement()->Velocity;
	FVector NewVelocity = CurrentVelocity + Steering;
	NewVelocity = NewVelocity.GetClampedToMaxSize(MaxSpeed);

	FVector Direction = NewVelocity.GetSafeNormal();
	AddMovementInput(Direction, 1.0f);

	FRotator NewRotation = UKismetMathLibrary::MakeRotFromX(NewVelocity);
	FRotator SmoothedRotation = FMath::RInterpTo(GetActorRotation(), NewRotation, GetWorld()->GetDeltaSeconds(), InterpeSpeedRotation);
	SetActorRotation(SmoothedRotation);
}


FVector ANPlayerCharacter::CalculateSteeringForce(const FVector& DesiredVelocity, const float InterpeSpeedSterring) const {
	FVector CurrentVelocity = GetCharacterMovement()->Velocity;
	FVector Steering = DesiredVelocity - CurrentVelocity;
	Steering = FMath::VInterpTo(CurrentVelocity, Steering, GetWorld()->GetDeltaSeconds(), InterpeSpeedSterring);
	return Steering.GetClampedToMaxSize(MaxForce);
}


void ANPlayerCharacter::SeekBehavior(const FVector& Target, float InterpeSpeedRotation, float InterpeSpeedSteering) {
	FVector CurrentPosition = GetActorLocation();
	FVector DesiredVelocity = (Target - CurrentPosition).GetSafeNormal() * MaxSpeed;
	FVector Steering = CalculateSteeringForce(DesiredVelocity, InterpeSpeedSteering);
	MoveWithSteering(Steering, InterpeSpeedRotation);
}


void ANPlayerCharacter::FleeBehavior(const FVector& Target, float InterpeSpeedRotation, float InterpeSpeedSteering) {
	FVector CurrentPosition = GetActorLocation();
	FVector DesiredVelocity = (CurrentPosition - Target).GetSafeNormal() * MaxSpeed;
	FVector Steering = CalculateSteeringForce(DesiredVelocity, InterpeSpeedSteering);
	MoveWithSteering(Steering,InterpeSpeedRotation);
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

	SeekBehavior(PredictedTarget, 15.0f, 15.0f);
}


void ANPlayerCharacter::EvadeBehavior(const FVector& Target) {
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

	FleeBehavior(PredictedTarget, 15.0f, 15.0f);
}




void ANPlayerCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (PlayerPawn) {
		FVector TargetLocation = PlayerPawn->GetActorLocation();
		ExecuteCurrentBehavior(TargetLocation);
	}
}