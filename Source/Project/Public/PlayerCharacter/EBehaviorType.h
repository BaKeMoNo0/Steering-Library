// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EBehaviorType.generated.h"


UENUM(BlueprintType)
enum UEBehaviorType : uint8 {
	None UMETA(DisplayName = "None"),
	Walk UMETA(DisplayName = "Walk"),
	Seek UMETA(DisplayName = "Seek"),
	Flee UMETA(DisplayName = "Flee"),
	Pursuit UMETA(DisplayName = "Pursuit"),
	Evade UMETA(DisplayName = "Evade"),
	Arrival UMETA(DisplayName = "Arrival"),
	Circuit UMETA(DisplayName = "Circuit"),
	OneWay UMETA(DisplayName = "OneWay"),
};
