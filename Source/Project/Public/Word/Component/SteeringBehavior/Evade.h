// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerCharacter/NPlayerCharacter.h"
#include "PlayerCharacter/PlayerCharacter.h"
#include "Evade.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_API UEvade : public UActorComponent {
	GENERATED_BODY()

public:	
	void ExecuteBehavior(ANPlayerCharacter* NPC, FVector TargetLocation, APlayerCharacter* Player);	
};
