// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EBehaviorType.generated.h"


UENUM(BlueprintType)
enum UEBehaviorType : uint8 {
	None UMETA(DisplayName = "None"),
	Seek UMETA(DisplayName = "Seek"),
	Flee UMETA(DisplayName = "Flee"),
};
