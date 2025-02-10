// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EBehaviorType.h"
#include "Path.h"
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
	float Mass;
	APawn* PlayerPawn;
	UPROPERTY(EditAnywhere, Category = "Path Following")
	APath* PathToFollow;
	
	UEBehaviorType CurrentBehavior;
	void ExecuteCurrentBehavior(FVector TargetLocation);
	void SetBehavior(UEBehaviorType NewBehavior);
	FVector CalculateSteeringForce(const FVector& DesiredVelocity);
	void MoveWithSteering(const FVector& Steering);
	
	void SeekBehavior(const FVector& Target);
	void FleeBehavior(const FVector& Target);
	void PursuitBehavior(const FVector& Target);
	void EvadeBehavior(const FVector& Target);
	void ArrivalBehavior(const FVector& Target);
	void CircuitBehavior();
	void OneWayBehavior();
	void TwoWayBehavior();
	FVector GetNextTargetOnSpline(int& CurrentIndex);
	int NearestSplinePoint();

	private:
	float AcceptanceRadius = 200.0f;
	int CurrentSplineIndex = -1;
	bool bIsReversing;
	FVector Velocity = FVector::ZeroVector;
};
