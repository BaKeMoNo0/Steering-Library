// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Seek.generated.h"


class USteeringComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_API USeek : public UActorComponent {
	GENERATED_BODY()
public:
	void ExecuteBehavior(ACharacter* NPC, FVector TargetLocation, USteeringComponent* SteeringComp);
};
