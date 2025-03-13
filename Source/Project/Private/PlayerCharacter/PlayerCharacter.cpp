// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter/PlayerCharacter.h"

class UEnhancedInputLocalPlayerSubsystem;


void APlayerCharacter::BeginPlay() {
	Super::BeginPlay();
}



void APlayerCharacter::SetBehavior(const UEBehaviorType NewBehavior){
	CurrentBehavior = NewBehavior;
}

