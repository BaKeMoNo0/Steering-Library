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
		SeekBehavior(TargetLocation);
		break;
	case Flee:
		FleeBehavior(TargetLocation);
		break;
	case Pursuit:
		PursuitBehavior(TargetLocation);
		break;
	default:
		break;
	}
}


void ANPlayerCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (PlayerPawn) {
		FVector TargetLocation = PlayerPawn->GetActorLocation();
		ExecuteCurrentBehavior(TargetLocation);
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


void ANPlayerCharacter::SeekBehavior(const FVector& Target) {
	FVector CurrentPosition = GetActorLocation();
	FVector DesiredVelocity = (Target - CurrentPosition).GetSafeNormal() * MaxSpeed;
	FVector Steering = CalculateSteeringForce(DesiredVelocity, 10.0f);
	MoveWithSteering(Steering, 9.0f);
}


void ANPlayerCharacter::FleeBehavior(const FVector& Target) {
	FVector CurrentPosition = GetActorLocation();
	FVector DesiredVelocity = (CurrentPosition - Target).GetSafeNormal() * MaxSpeed;
	FVector Steering = CalculateSteeringForce(DesiredVelocity, 12.0f);
	MoveWithSteering(Steering,11.0f);
}


void ANPlayerCharacter::PursuitBehavior(const FVector& Target) {
	FVector CurrentPosition = GetActorLocation();
	FVector TargetVelocity = PlayerPawn->GetVelocity();
	float DistanceToTarget = FVector::Dist(CurrentPosition, Target);

	FVector ToTarget = (Target - CurrentPosition).GetSafeNormal();
	float Alignment = FVector::DotProduct(ToTarget, TargetVelocity.GetSafeNormal());

	float c = FMath::Lerp(0.3f, 1.0f, 1.0f - (Alignment * 0.5f));
	float PredictionTime = (DistanceToTarget / MaxSpeed) * c;
	FVector PredictedTarget = Target + TargetVelocity * PredictionTime;

	FVector DesiredVelocity = (PredictedTarget - CurrentPosition).GetSafeNormal() * MaxSpeed;
	FVector Steering = CalculateSteeringForce(DesiredVelocity, 15);
	MoveWithSteering(Steering, 15);
}