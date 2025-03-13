// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimplePath.h"
#include "GameFramework/Actor.h"
#include "IntersectionPath.generated.h"

class ANPCCharacter;

UCLASS()
class PROJECT_API AIntersectionPath : public AActor {
	GENERATED_BODY()

	void DebugLine();
	
public:
	AIntersectionPath();

	UPROPERTY(BlueprintReadOnly, Category="Paths")
	TArray<ASimplePath*> ConnectedPaths;
	UPROPERTY()
	ANPCCharacter* ChickenTarget = nullptr;
	void GetAllNeighbors();
	
protected:
	virtual void BeginPlay() override;
};
