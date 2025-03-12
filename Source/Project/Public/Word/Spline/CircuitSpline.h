// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "PlayerCharacter/NPlayerCharacter.h"
#include "PlayerCharacter/PlayerCharacter.h"
#include "CircuitSpline.generated.h"

UCLASS()
class PROJECT_API ACircuitSpline : public AActor {
	GENERATED_BODY()
	
public:
	ACircuitSpline();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	ANPlayerCharacter* NCPRef;
	UPROPERTY()
	APlayerCharacter* PlayerCharacter;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Path")
	USplineComponent* SplineComponent;

};
