// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NPC_AIController.generated.h"


class ANPCCharacter;
class USteeringComponent;
class USeek;

UCLASS()
class PROJECT_API ANPC_AIController : public AAIController {
	GENERATED_BODY()

	FVector CurrentTargetLocation;
	UPROPERTY()
	ANPCCharacter* OwnerCharacter;
	void CheckDistanceToTarget();
	
public:
	FTimerHandle DistanceCheckTimer;
	
    virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;

    void MoveToTarget(FVector TargetLocation);
};
