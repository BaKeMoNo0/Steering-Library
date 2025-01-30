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
		if (SeekAction){
			EnhancedInputComponent->BindAction(SeekAction, ETriggerEvent::Triggered, this, &APlayerCharacter::SetSeekBehaviorOnNPC);
		}
		if (FleeAction){
			EnhancedInputComponent->BindAction(FleeAction, ETriggerEvent::Triggered, this, &APlayerCharacter::SetFleeBehaviorOnNPC);
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

