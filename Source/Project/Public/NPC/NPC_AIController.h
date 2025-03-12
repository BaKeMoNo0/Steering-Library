// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NPC_AIController.generated.h"


UCLASS()
class PROJECT_API ANPC_AIController : public AAIController {
	GENERATED_BODY()

public:
    virtual void BeginPlay() override;

    void MoveToTarget(FVector TargetLocation);

protected:
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
};
