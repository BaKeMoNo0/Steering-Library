// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter/PlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "UI/MainMenuWidget.h"

class UEnhancedInputLocalPlayerSubsystem;

APlayerCharacter::APlayerCharacter() {
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerCharacter::BeginPlay() {
	Super::BeginPlay();
	NPCRef = Cast<ANPlayerCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), ANPlayerCharacter::StaticClass()));
	GameMode = Cast<AProjectGameMode>(GetWorld()->GetAuthGameMode());

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController())) {
		if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer()) {
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()) {
				if (InputMappingContext) {
					Subsystem->AddMappingContext(InputMappingContext, 0);
				}
			}
		}
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent)) {
		if (SeekAction) {
			EnhancedInputComponent->BindAction(SeekAction, ETriggerEvent::Triggered, this, &APlayerCharacter::SetSeekBehaviorOnNPC);
		}
		if (FleeAction) {
			EnhancedInputComponent->BindAction(FleeAction, ETriggerEvent::Triggered, this, &APlayerCharacter::SetFleeBehaviorOnNPC);
		}
		if (PursuitAction) {
			EnhancedInputComponent->BindAction(PursuitAction, ETriggerEvent::Triggered, this, &APlayerCharacter::SetPursuitBehaviorOnNPC);
		}
		if (EvadeAction) {
			EnhancedInputComponent->BindAction(EvadeAction, ETriggerEvent::Triggered, this, &APlayerCharacter::SetEvadeBehaviorOnNPC);
		}
		if (ArrivalAction) {
			EnhancedInputComponent->BindAction(ArrivalAction, ETriggerEvent::Triggered, this, &APlayerCharacter::SetArrivalBehaviorOnNPC);
		}
		if (CircuitAction) {
			EnhancedInputComponent->BindAction(CircuitAction, ETriggerEvent::Triggered, this, &APlayerCharacter::SetCircuitBehaviorOnNPC);
		}
		if (OneWayAction){
			EnhancedInputComponent->BindAction(OneWayAction, ETriggerEvent::Triggered, this, &APlayerCharacter::SetOneWayBehaviorOnNPC);
		}
		if (TwoWayAction){
			EnhancedInputComponent->BindAction(TwoWayAction, ETriggerEvent::Triggered, this, &APlayerCharacter::SetTwoWayBehaviorOnNPC);
		}
	}
}

void APlayerCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}


void APlayerCharacter::SetSeekBehaviorOnNPC() {
	if (NPCRef) {
		NPCRef->SetBehavior(UEBehaviorType::Seek);
		GameMode->MainMenuWidget->UpdateText("Seek");
	}
}

void APlayerCharacter::SetFleeBehaviorOnNPC() {
	if (NPCRef) {
		NPCRef->SetBehavior(UEBehaviorType::Flee);
		GameMode->MainMenuWidget->UpdateText("Flee");
	}
}

void APlayerCharacter::SetPursuitBehaviorOnNPC() {
	if (NPCRef) {
		NPCRef->SetBehavior(UEBehaviorType::Pursuit);
		GameMode->MainMenuWidget->UpdateText("Pursuit");
	}
}

void APlayerCharacter::SetEvadeBehaviorOnNPC() {
	if (NPCRef) {
		NPCRef->SetBehavior(UEBehaviorType::Evade);
		GameMode->MainMenuWidget->UpdateText("Evade");
	}
}

void APlayerCharacter::SetArrivalBehaviorOnNPC() {
	if (NPCRef) {
		NPCRef->SetBehavior(UEBehaviorType::Arrival);
		GameMode->MainMenuWidget->UpdateText("Arrival");
	}
}

void APlayerCharacter::SetCircuitBehaviorOnNPC() {
	if (NPCRef) {
		NPCRef->SetBehavior(UEBehaviorType::Circuit);
		GameMode->MainMenuWidget->UpdateText("Circuit");
	}
}

void APlayerCharacter::SetOneWayBehaviorOnNPC() {
	if (NPCRef) {
		NPCRef->SetBehavior(UEBehaviorType::OneWay);
		GameMode->MainMenuWidget->UpdateText("OneWay");
	}
}

void APlayerCharacter::SetTwoWayBehaviorOnNPC() {
	if (NPCRef) {
		NPCRef->SetBehavior(UEBehaviorType::TwoWay);
		GameMode->MainMenuWidget->UpdateText("TwoWay");
	}
}


