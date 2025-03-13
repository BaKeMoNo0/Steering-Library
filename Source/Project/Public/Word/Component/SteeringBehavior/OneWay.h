// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerCharacter/NPlayerCharacter.h"
#include "OneWay.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_API UOneWay : public UActorComponent {
	GENERATED_BODY()

	float AcceptanceRadius = 200.0f;
	int CurrentSplineIndex = -1;
public:
	void ExecuteBehavior(ANPlayerCharacter* NPC);	
};
