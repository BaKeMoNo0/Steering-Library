// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter/NPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ANPlayerCharacter::ANPlayerCharacter() {
 	PrimaryActorTick.bCanEverTick = true;
	MaxSpeed = 600.0f;
	CurrentBehavior = None;
}

void ANPlayerCharacter::SetBehavior(UEBehaviorType NewBehavior){
	CurrentBehavior = NewBehavior;
}

void ANPlayerCharacter::ExecuteCurrentBehavior(FVector TargetLocation) {
	switch (CurrentBehavior) {
	case Seek:
		SeekBehavior(TargetLocation);
		break;
	case Flee:
			break;
	default:
		break;
	}
}


void ANPlayerCharacter::BeginPlay() {
	Super::BeginPlay();
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
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

	FVector DesiredVelocity = (Target - CurrentPosition).GetSafeNormal() * MaxSpeed;
	FVector CurrentVelocity = GetCharacterMovement()->Velocity;
	FVector Steering = DesiredVelocity - CurrentVelocity;
	AddMovementInput(Steering);
	//GetCharacterMovement()->Velocity = NewVelocity;

	FVector NewVelocity = CurrentVelocity + Steering;
	NewVelocity = NewVelocity.GetClampedToMaxSize(MaxSpeed);
	FRotator NewRotation = UKismetMathLibrary::MakeRotFromX(NewVelocity);
	SetActorRotation(NewRotation);
}
