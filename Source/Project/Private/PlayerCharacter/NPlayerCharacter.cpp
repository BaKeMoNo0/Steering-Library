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

void ANPlayerCharacter::SeekBehavior(const FVector& Target) {
	FVector CurrentPosition = GetActorLocation();
	FVector CurrentVelocity = GetCharacterMovement()->Velocity;

	FVector DesiredVelocity = (Target - CurrentPosition).GetSafeNormal() * MaxSpeed;
	FVector Steering = DesiredVelocity - CurrentVelocity;
	Steering = FMath::VInterpTo(CurrentVelocity, Steering, GetWorld()->GetDeltaSeconds(), 9.0f);
	Steering = Steering.GetClampedToMaxSize(MaxForce);

	FVector NewVelocity = CurrentVelocity + Steering;
	NewVelocity = NewVelocity.GetClampedToMaxSize(MaxSpeed);

	FVector Direction = NewVelocity.GetSafeNormal();
	AddMovementInput(Direction, 1.0f);

	FRotator NewRotation = UKismetMathLibrary::MakeRotFromX(NewVelocity);
	FRotator SmoothedRotation = FMath::RInterpTo(GetActorRotation(), NewRotation, GetWorld()->GetDeltaSeconds(), 10.0f);
	SetActorRotation(SmoothedRotation);
}

void ANPlayerCharacter::FleeBehavior(const FVector& Target) {
	FVector CurrentPosition = GetActorLocation();
	FVector CurrentVelocity = GetCharacterMovement()->Velocity;

	FVector DesiredVelocity = (CurrentPosition - Target).GetSafeNormal() * MaxSpeed;
	FVector Steering = DesiredVelocity - CurrentVelocity;
	Steering = FMath::VInterpTo(CurrentVelocity, Steering, GetWorld()->GetDeltaSeconds(), 9.0f);
	Steering = Steering.GetClampedToMaxSize(MaxForce);

	FVector NewVelocity = CurrentVelocity + Steering;
	NewVelocity = NewVelocity.GetClampedToMaxSize(MaxSpeed);

	FVector Direction = NewVelocity.GetSafeNormal();
	AddMovementInput(Direction, 1.0f);

	FRotator NewRotation = UKismetMathLibrary::MakeRotFromX(NewVelocity);
	FRotator SmoothedRotation = FMath::RInterpTo(GetActorRotation(), NewRotation, GetWorld()->GetDeltaSeconds(), 10.0f);
	SetActorRotation(SmoothedRotation);
}