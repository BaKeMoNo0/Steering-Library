// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "Path.generated.h"

class ANPlayerCharacter;

UCLASS()
class PROJECT_API APath : public AActor {
	GENERATED_BODY()
	
public:
	APath();
	
	ANPlayerCharacter* PlayerCharacter; 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Path")
	USplineComponent* SplineComponent;


protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
