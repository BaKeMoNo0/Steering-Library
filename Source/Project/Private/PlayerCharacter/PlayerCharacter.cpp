// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter/PlayerCharacter.h"
#include "PlayerCharacter/NCPMovementComponent.h"

class UEnhancedInputLocalPlayerSubsystem;


void APlayerCharacter::BeginPlay() {
	Super::BeginPlay();
	NPCMovementComponent = FindComponentByClass<UNCPMovementComponent>(); 
}


