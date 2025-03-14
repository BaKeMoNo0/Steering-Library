// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeLab2.h"

#include "Kismet/GameplayStatics.h"
#include "Word/Component/ChickenHandlerComponent.h"
#include "Word/Component/PathFindingManager.h"
#include "Word/Path/IntersectionPath.h"
#include "Word/Spawn/SpawnManager.h"

void AGameModeLab2::BeginPlay() {
	Super::BeginPlay();
	InitAllIntersectionPath();
	InitSimplePath();
	SpawnManagerSetup();
	InitNcpCharacter();
}

void AGameModeLab2::InitAllIntersectionPath() {
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AIntersectionPath::StaticClass(), FoundActors);
	for (AActor* Actor : FoundActors) {
		if (AIntersectionPath* Intersection = Cast<AIntersectionPath>(Actor)) {
			Intersection->GetAllNeighbors();
			AllIntersections.Add(Intersection);
			if (Intersection->ActorHasTag("Farm")){
				FarmIntersection = Intersection;
			}
		}
	}
}

void AGameModeLab2::InitSimplePath() {
	for (AIntersectionPath* Intersection : AllIntersections) {
		for (ASimplePath* Path : Intersection->ConnectedPaths) {
			if (Path) Path->InitializeIntersections();
		}
	}
}


void AGameModeLab2::SpawnManagerSetup() {
	SpawnManager = Cast<ASpawnManager>(UGameplayStatics::GetActorOfClass(GetWorld(),ASpawnManager::StaticClass()));

	if (!SpawnManager) {
		GetWorld()->SpawnActor<ASpawnManager>(ASpawnManager::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
	}
	if (SpawnManager) {
		SpawnManager->SpawnChickensCharacter();
		SpawnManager->SpawnFarmerCharacter();
	}
}

void AGameModeLab2::InitNcpCharacter() {
	for (ANPCCharacter * Chicken : SpawnManager->SpawnedChickens){
		Chicken->CheckOverlappingPaths();
	}
	for (ANPCCharacter * Farmer : SpawnManager->SpawnedFarmers){
		Farmer->CheckOverlappingPaths();
		Farmer->FarmIntersection = FarmIntersection;
		if (Farmer->PathFindingManager) {
			Farmer->PathFindingManager->AllIntersections = AllIntersections;
			Farmer->PathFindingManager->ChickensTargets = SpawnManager->SpawnedChickens;
		}
		if (Farmer->StartingIntersectionPath && Farmer->PathFindingManager) {
			Farmer->PathFindingManager->CalculatePath();
			//TArray<AIntersectionPath*> Path = Farmer->PathFindingManager->FindPathToClosestChicken();
			//Farmer->PathFindingManager->MoveToIntersection(Path);
		}
	}
}
