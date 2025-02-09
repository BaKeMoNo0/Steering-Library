// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "NPlayerCharacter.h"
#include "GameFramework/Character.h"
#include "Project/ProjectGameMode.h"
#include "PlayerCharacter.generated.h"

class UInputMappingContext;

UCLASS()
class PROJECT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	// Input bindings
	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* SeekAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* FleeAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* PursuitAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* EvadeAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* ArrivalAction;
	
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* CircuitAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* OneWayAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* TwoWayAction;
	
	ANPlayerCharacter* NPCRef;
	AProjectGameMode* GameMode;
	
	void SetSeekBehaviorOnNPC();
	void SetFleeBehaviorOnNPC();
	void SetPursuitBehaviorOnNPC();
	void SetEvadeBehaviorOnNPC();
	void SetArrivalBehaviorOnNPC();
	void SetCircuitBehaviorOnNPC();
	void SetOneWayBehaviorOnNPC();
	void SetTwoWayBehaviorOnNPC();
};
