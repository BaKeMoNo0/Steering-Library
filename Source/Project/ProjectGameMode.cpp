// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectGameMode.h"
#include "ProjectCharacter.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"


void AProjectGameMode::BeginPlay(){
	Super::BeginPlay();
	PlayerController = GetWorld()->GetFirstPlayerController();
	if (MainMenuWidgetClass) {
		MainMenuWidget = Cast<UMainMenuWidget>(CreateWidget(GetWorld(), MainMenuWidgetClass));
		if (MainMenuWidget) {
			MainMenuWidget->AddToViewport();
		}
	}
}
