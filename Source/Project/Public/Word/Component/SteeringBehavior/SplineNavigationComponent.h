// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerCharacter/NPlayerCharacter.h"
#include "Word/Spline/CircuitSpline.h"
#include "SplineNavigationComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_API USplineNavigationComponent : public UActorComponent {
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;


public:
	UPROPERTY()
	ACircuitSpline* PathToFollow;
	
	FVector GetNextTargetOnSpline(ANPlayerCharacter* NPC, int& CurrentIndex);
	int NearestSplinePoint(ANPlayerCharacter* NPC);
};
