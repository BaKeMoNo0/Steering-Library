// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerCharacter/NPlayerCharacter.h"
#include "Flee.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_API UFlee : public UActorComponent {
	GENERATED_BODY()
	float MaxSpeed = 400.0f;

public:
	void ExecuteBehavior(ANPlayerCharacter* NPC, FVector TargetLocation);
};
