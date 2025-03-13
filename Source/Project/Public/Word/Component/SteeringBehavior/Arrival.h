// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerCharacter/NPlayerCharacter.h"
#include "Arrival.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_API UArrival : public UActorComponent {
	GENERATED_BODY()
	FVector Velocity = FVector::ZeroVector;
	float MaxSpeed = 400.0f;
	float Mass = 40.0f;

public:	
	void ExecuteBehavior(ANPlayerCharacter* NPC, FVector TargetLocation);	
};
