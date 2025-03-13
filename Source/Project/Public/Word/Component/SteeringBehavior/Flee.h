// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Flee.generated.h"


class USteeringComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_API UFlee : public UActorComponent {
	GENERATED_BODY()
	float MaxSpeed = 400.0f;

public:
	void ExecuteBehavior(ACharacter* NPC, FVector TargetLocation, USteeringComponent* SteeringComp);
};
