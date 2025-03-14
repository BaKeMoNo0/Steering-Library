// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NPC/NPCCharacter.h"
#include "GameModeLab2.generated.h"


class ASpawnManager;
class AIntersectionPath;

UCLASS()
class PROJECT_API AGameModeLab2 : public AGameModeBase {
	GENERATED_BODY()

	UPROPERTY()
	ASpawnManager* SpawnManager;
	UPROPERTY()
	AIntersectionPath* FarmIntersection;
	UPROPERTY()
	TArray<AActor*> ParkingSpotsPoints;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ParkingSpotPointClass;
	
	void InitAllIntersectionPath();
	void InitSimplePath();
	void SpawnManagerSetup();
	void InitNcpCharacter();
	void InitParkingSpots();
	void StartPathFinding();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY()
	TArray<AIntersectionPath*> AllIntersections;
	UPROPERTY()
	TArray<ANPCCharacter*> ChickensTargets;
};
