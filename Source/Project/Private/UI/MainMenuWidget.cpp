// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenuWidget.h"

#include "PlayerCharacter/NPlayerCharacter.h"
#include "PlayerCharacter/PlayerCharacter.h"


void UMainMenuWidget::UpdateText(const FString& NewText) {
	if (MyTextBlock) {;
		MyTextBlock->SetText(FText::FromString(NewText));
	}
}

