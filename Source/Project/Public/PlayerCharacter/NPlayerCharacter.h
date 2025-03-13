// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPlayerCharacter.generated.h"

class USplineNavigationComponent;
class UNPCBehaviorManager;
class USteeringComponent;
class UTwoWay;
class UOneWay;
class UCircuit;
class UArrival;
class UEvade;
class UPursuit;
class UFlee;
class USeek;

UCLASS()
class PROJECT_API ANPlayerCharacter : public ACharacter {
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY()
	UNPCBehaviorManager* BehaviorManagerComp;
	UPROPERTY()
	USteeringComponent* SteeringComp;
	UPROPERTY()
	USeek* SeekComp;
	UPROPERTY()
	UFlee* FleeComp;
	UPROPERTY()
	UPursuit* PursuitComp;
	UPROPERTY()
	UEvade* EvadeComp;
	UPROPERTY()
	UArrival* ArrivalComp;
	UPROPERTY()
	USplineNavigationComponent* SplineComp;
	UPROPERTY()
	UCircuit* CircuitComp;
	UPROPERTY()
	UOneWay* OneWayComp;
	UPROPERTY()
	UTwoWay* TwoWayComp;
};
