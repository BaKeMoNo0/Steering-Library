// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EBehaviorType.h"
#include "GameFramework/Character.h"
#include "NPlayerCharacter.generated.h"

UCLASS()
class PROJECT_API ANPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ANPlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
	float MaxSpeed;
	float MaxForce;
	APawn* PlayerPawn;
	
	
	UEBehaviorType CurrentBehavior;
	void ExecuteCurrentBehavior(FVector TargetLocation);
	void SetBehavior(UEBehaviorType NewBehavior);
	void MoveWithSteering(const FVector& Steering, float InterpeSpeedRotation);
	FVector CalculateSteeringForce(const FVector& DesiredVelocity, float InterSpeedSteering) const;
	
	void SeekBehavior(const FVector& Target, float InterpeSpeedRotation, float InterpeSpeedSteering);
	void FleeBehavior(const FVector& Target, float InterpeSpeedRotation, float InterpeSpeedSteering);
	void PursuitBehavior(const FVector& Target);
	void EvadeBehavior(const FVector& Target);
};
