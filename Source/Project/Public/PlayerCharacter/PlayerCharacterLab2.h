// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacterLab2.generated.h"

UCLASS()
class PROJECT_API APlayerCharacterLab2 : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacterLab2();

protected:
	virtual void BeginPlay() override;
};
