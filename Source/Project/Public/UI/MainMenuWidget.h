// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "MainMenuWidget.generated.h"


UCLASS()
class PROJECT_API UMainMenuWidget : public UUserWidget {
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MyTextBlock;

public:
	UFUNCTION(Category = "UI")
	void UpdateText(const FString& NewText);
};
