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
	void SeekBehavior(const FVector& Target);
	void FleeBehavior(const FVector& Target);
};
