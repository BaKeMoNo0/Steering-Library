// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Word/Path/IntersectionPath.h"
#include "Word/Spawn/SpawnManager.h"
#include "PathFindingManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_API UPathFindingManager : public UActorComponent {
	GENERATED_BODY()
	
	TArray<AIntersectionPath*> Dijkstra(AIntersectionPath* StartPath, AIntersectionPath* TargetPath);

protected:
	virtual void BeginPlay() override;
	
public:
	UPROPERTY()
	TArray<AIntersectionPath*> AllIntersections;
	UPROPERTY()
	TArray<ANPCCharacter*> Farmers;
	UPROPERTY()
	ANPCCharacter* OwnerCharacter;
	UPROPERTY()
	ANPCCharacter* ChickenTarget;

	void MoveToIntersection(TArray<AIntersectionPath*> Path);
	void CalculatePath();
	void MoveToPosition(FVector TargetPosition);
	TArray<AIntersectionPath*> FindPathToClosestChicken();
	
};
