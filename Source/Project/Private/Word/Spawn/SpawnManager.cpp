// Fill out your copyright notice in the Description page of Project Settings.


#include "Word/Spawn/SpawnManager.h"

#include "Kismet/GameplayStatics.h"
#include "Runtime/Core/Tests/Containers/TestUtils.h"

ASpawnManager::ASpawnManager() {}


void ASpawnManager::BeginPlay() {
	Super::BeginPlay();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), SpawnPointClass, SpawnPoints);
}

void ASpawnManager::SpawnChickensCharacter() {
	if (!SpawnPointClass) return;
	if (SpawnPoints.Num() == 0 || !ChickenCharacterClass) return;

	Test::Shuffle(SpawnPoints);
	
	int32 ChickensSpawned = 0;

	for (AActor* SpawnLocation : SpawnPoints) {
		if (ChickensSpawned < NumberOfChickenToSpawn && SpawnLocation->ActorHasTag("Chicken")) {
			ANPCCharacter* SpawnedChicken = nullptr;
			FVector Location = FVector(SpawnLocation->GetActorLocation().X, SpawnLocation->GetActorLocation().Y, 108.0f);
			SpawnedChicken = GetWorld()->SpawnActor<ANPCCharacter>(ChickenCharacterClass,  Location, FRotator::ZeroRotator);
			SpawnedChickens.Add(SpawnedChicken);
			ChickensSpawned++;
		}

		if (ChickensSpawned >= NumberOfChickenToSpawn) {
			break;
		}
	}
}

void ASpawnManager::SpawnFarmerCharacter() {
	if (!SpawnPointClass) return;
	if (SpawnPoints.Num() == 0 || !FarmerCharacterClass) return;
	

	Test::Shuffle(SpawnPoints);
	
	int32 FarmersSpawned = 0;

	for (AActor* SpawnLocation : SpawnPoints) {
		if (FarmersSpawned < NumberOfFarmerToSpawn && SpawnLocation->ActorHasTag("Farmer")) {
			ANPCCharacter* SpawnedFarmer = nullptr;
			FVector Location = FVector(SpawnLocation->GetActorLocation().X, SpawnLocation->GetActorLocation().Y, 140.0f);
			SpawnedFarmer = GetWorld()->SpawnActor<ANPCCharacter>(FarmerCharacterClass, Location, FRotator::ZeroRotator);
			SpawnedFarmers.Add(SpawnedFarmer);
			FarmersSpawned++;
		}

		if (FarmersSpawned >= NumberOfFarmerToSpawn) {
			break;
		}
	}
}

