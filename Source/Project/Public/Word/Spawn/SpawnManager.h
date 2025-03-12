// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NPC/NPCCharacter.h"
#include "SpawnManager.generated.h"

UCLASS()
class PROJECT_API ASpawnManager : public AActor {
	GENERATED_BODY()

	UPROPERTY()
	TArray<AActor*> SpawnPoints;
	
public:
	ASpawnManager();

	UPROPERTY()
	TArray<ANPCCharacter*> SpawnedChickens;
	UPROPERTY()
	TArray<ANPCCharacter*> SpawnedFarmers;
	void SpawnChickensCharacter();
	void SpawnFarmerCharacter();

protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category="Spawn")
	TSubclassOf<ANPCCharacter> ChickenCharacterClass;

	UPROPERTY(EditAnywhere, Category="Spawn")
	TSubclassOf<ANPCCharacter> FarmerCharacterClass;
	
	UPROPERTY(EditAnywhere, Category="Spawn")
	TSubclassOf<AActor> SpawnPointClass;

	UPROPERTY(EditAnywhere, Category="Spawn")
	int32 NumberOfChickenToSpawn = 3;

	UPROPERTY(EditAnywhere, Category="Spawn")
	int32 NumberOfFarmerToSpawn = 1;
	
};
