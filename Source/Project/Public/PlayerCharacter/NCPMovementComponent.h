// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EBehaviorType.h"
#include "PlayerCharacter.h"
#include "Components/ActorComponent.h"
#include "Word/Spline/CircuitSpline.h"
#include "NCPMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_API UNCPMovementComponent : public UActorComponent {
	GENERATED_BODY()
	
	float AcceptanceRadius = 200.0f;
	int CurrentSplineIndex = -1;
	bool bIsReversing;
	FVector Velocity = FVector::ZeroVector;
	float MaxSpeed;
	float MaxForce;
	float Mass;
	
public:
	UNCPMovementComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY()
	ANPlayerCharacter* NPCRef;
	UPROPERTY()
	ACircuitSpline* PathToFollow;
	UPROPERTY()
	APlayerCharacter* OwnerCharacter;

	UEBehaviorType CurrentBehavior;

	void ExecuteCurrentBehavior(FVector TargetLocation);
	
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

	void SetBehavior(const UEBehaviorType NewBehavior);
};
