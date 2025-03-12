// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameModeLab2.generated.h"


class ASpawnManager;
class AIntersectionPath;

UCLASS()
class PROJECT_API AGameModeLab2 : public AGameModeBase {
	GENERATED_BODY()

	UPROPERTY()
	AIntersectionPath* IntersectionPath;
	UPROPERTY()
	ASpawnManager* SpawnManager;
	
	void InitAllIntersectionPath();
	void InitSimplePath();
	void SpawnManagerSetup();
	void InitNcpCharacter();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY()
	TArray<AIntersectionPath*> AllIntersections;	
};
