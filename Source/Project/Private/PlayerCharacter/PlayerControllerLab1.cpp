// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter/PlayerControllerLab1.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void APlayerControllerLab1::BeginPlay() {
	Super::BeginPlay();
	
	ControlledCharacter = Cast<APlayerCharacter>(GetPawn());
	
	FInputModeUIOnly InputMode;
	if (MainMenuWidgetClass) {
		MainMenuWidget = Cast<UMainMenuWidget>(CreateWidget(GetWorld(), MainMenuWidgetClass));
		if (MainMenuWidget) {
			MainMenuWidget->AddToViewport();
		}
	}
}

void APlayerControllerLab1::SetupInputComponent() {
	Super::SetupInputComponent();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer())) {
		if (InputMappingContext) {
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent)) {
		if (SeekAction) {
			EnhancedInputComponent->BindAction(SeekAction, ETriggerEvent::Triggered, this, &APlayerControllerLab1::SetSeekBehaviorOnNPC);
		}
		if (FleeAction) {
			EnhancedInputComponent->BindAction(FleeAction, ETriggerEvent::Triggered, this, &APlayerControllerLab1::SetFleeBehaviorOnNPC);
		}
		if (PursuitAction) {
			EnhancedInputComponent->BindAction(PursuitAction, ETriggerEvent::Triggered, this, &APlayerControllerLab1::SetPursuitBehaviorOnNPC);
		}
		if (EvadeAction) {
			EnhancedInputComponent->BindAction(EvadeAction, ETriggerEvent::Triggered, this, &APlayerControllerLab1::SetEvadeBehaviorOnNPC);
		}
		if (ArrivalAction) {
			EnhancedInputComponent->BindAction(ArrivalAction, ETriggerEvent::Triggered, this, &APlayerControllerLab1::SetArrivalBehaviorOnNPC);
		}
		if (CircuitAction) {
			EnhancedInputComponent->BindAction(CircuitAction, ETriggerEvent::Triggered, this, &APlayerControllerLab1::SetCircuitBehaviorOnNPC);
		}
		if (OneWayAction){
			EnhancedInputComponent->BindAction(OneWayAction, ETriggerEvent::Triggered, this, &APlayerControllerLab1::SetOneWayBehaviorOnNPC);
		}
		if (TwoWayAction){
			EnhancedInputComponent->BindAction(TwoWayAction, ETriggerEvent::Triggered, this, &APlayerControllerLab1::SetTwoWayBehaviorOnNPC);
		}
	}
}

void APlayerControllerLab1::SetSeekBehaviorOnNPC() {
	ControlledCharacter->SetBehavior(UEBehaviorType::Seek);
	MainMenuWidget->UpdateText("Seek");
}

void APlayerControllerLab1::SetFleeBehaviorOnNPC() {
	ControlledCharacter->SetBehavior(UEBehaviorType::Flee);
	MainMenuWidget->UpdateText("Flee");
}

void APlayerControllerLab1::SetPursuitBehaviorOnNPC() {
	ControlledCharacter->SetBehavior(UEBehaviorType::Pursuit);
	MainMenuWidget->UpdateText("Pursuit");
}

void APlayerControllerLab1::SetEvadeBehaviorOnNPC() {
	ControlledCharacter->SetBehavior(UEBehaviorType::Evade);
	MainMenuWidget->UpdateText("Evade");
}

void APlayerControllerLab1::SetArrivalBehaviorOnNPC() {
	ControlledCharacter->SetBehavior(UEBehaviorType::Arrival);
	MainMenuWidget->UpdateText("Arrival");
}

void APlayerControllerLab1::SetCircuitBehaviorOnNPC() {
	ControlledCharacter->SetBehavior(UEBehaviorType::Circuit);
	MainMenuWidget->UpdateText("Circuit");
}

void APlayerControllerLab1::SetOneWayBehaviorOnNPC() {
	ControlledCharacter->SetBehavior(UEBehaviorType::OneWay);
	MainMenuWidget->UpdateText("OneWay");
}

void APlayerControllerLab1::SetTwoWayBehaviorOnNPC() {
	ControlledCharacter->SetBehavior(UEBehaviorType::TwoWay);
	MainMenuWidget->UpdateText("TwoWay");
}
