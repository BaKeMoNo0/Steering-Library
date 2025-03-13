// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TwoWay.generated.h"


class UArrival;
class USteeringComponent;
class USplineNavigationComponent;
class USeek;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_API UTwoWay : public UActorComponent {
	GENERATED_BODY()
	float AcceptanceRadius = 200.0f;
	int CurrentSplineIndex = -1;
	bool bIsReversing = false;

public:	
	void ExecuteBehavior(ACharacter* NPC, USeek* SeekComp, USplineNavigationComponent* SplineComp, USteeringComponent* SteeringComp, UArrival* ArrivalComp);
		
};
