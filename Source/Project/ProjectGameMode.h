// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UI/MainMenuWidget.h"
#include "ProjectGameMode.generated.h"

UCLASS(minimalapi)
class AProjectGameMode : public AGameModeBase {
	GENERATED_BODY()

	
protected:
	virtual void BeginPlay() override;
};



