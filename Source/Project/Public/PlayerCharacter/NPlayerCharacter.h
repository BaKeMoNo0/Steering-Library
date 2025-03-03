// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EBehaviorType.h"
#include "Path.h"
#include "GameFramework/Character.h"
#include "NPlayerCharacter.generated.h"

UCLASS()
class PROJECT_API ANPlayerCharacter : public ACharacter {
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
};
