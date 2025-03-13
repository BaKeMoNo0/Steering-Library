// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Evade.generated.h"


class USteeringComponent;
class UFlee;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_API UEvade : public UActorComponent {
	GENERATED_BODY()

public:	
	void ExecuteBehavior(ACharacter* NPC, FVector TargetLocation, ACharacter* Player, UFlee* FleeComp, USteeringComponent* SteeringComp);	
};
