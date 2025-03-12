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
	
	TArray<AIntersectionPath*> Dijkstra();

protected:
	virtual void BeginPlay() override;
	
public:
	UPathFindingManager();

	UPROPERTY()
	TArray<AIntersectionPath*> AllIntersections;
	UPROPERTY()
	TArray<ANPCCharacter*> ChickensTargets;
	UPROPERTY()
	ANPCCharacter* OwnerCharacter;

	void MoveToTarget(ANPCCharacter* NPC);
	void RecalculatePath(ANPCCharacter* NPC);
	
};
