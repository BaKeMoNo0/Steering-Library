// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "PlayerCharacter.h"
#include "GameFramework/PlayerController.h"
#include "UI/MainMenuWidget.h"
#include "PlayerControllerLab1.generated.h"


UCLASS()
class PROJECT_API APlayerControllerLab1 : public APlayerController {
	GENERATED_BODY()

	UPROPERTY()
	APlayerCharacter* ControlledCharacter;
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
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

public:
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> MainMenuWidgetClass;
	UPROPERTY(BlueprintReadOnly, Category = "UI")
	UMainMenuWidget* MainMenuWidget;

	void SetSeekBehaviorOnNPC();
	void SetFleeBehaviorOnNPC();
	void SetPursuitBehaviorOnNPC();
	void SetEvadeBehaviorOnNPC();
	void SetArrivalBehaviorOnNPC();
	void SetCircuitBehaviorOnNPC();
	void SetOneWayBehaviorOnNPC();
	void SetTwoWayBehaviorOnNPC();
};
