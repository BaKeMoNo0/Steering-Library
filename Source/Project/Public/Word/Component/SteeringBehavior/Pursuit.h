// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Pursuit.generated.h"


class USteeringComponent;
class USeek;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_API UPursuit : public UActorComponent
{
	GENERATED_BODY()

public:	
	void ExecuteBehavior(ACharacter* NPC, FVector TargetLocation, ACharacter* Player, USeek* SeekComp, USteeringComponent* SteeringComp);	
};
