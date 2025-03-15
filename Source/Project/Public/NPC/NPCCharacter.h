// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPC_AIController.h"
#include "GameFramework/Character.h"
#include "Word/Path/SimplePath.h"
#include "NPCCharacter.generated.h"

class AGameModeLab2;
class UPlannerComponent;
class USteeringComponent;
class USeek;
class UArrival;
class UChickenHandlerComponent;
class UPathFindingManager;

UCLASS()
class PROJECT_API ANPCCharacter : public ACharacter {
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* CollisionBox;

	int CurrentPathIndex;

public:
	ANPCCharacter();
	UPROPERTY()
	USeek* SeekComp;
	UPROPERTY()
	UArrival* ArrivalComp;
	UPROPERTY()
	USteeringComponent* SteeringComp;
	UPROPERTY()
	UPathFindingManager* PathFindingManager;
	UPROPERTY()
	ANPC_AIController* AIController;
	UPROPERTY()
	UChickenHandlerComponent* ChickenHandler;
	UPROPERTY()
	AActor* ParkingSpot;
	UPROPERTY()
	AGameModeLab2* GameModeLab2;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pathfinding")
	AIntersectionPath* FarmIntersection;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Pathfinding")
	AIntersectionPath* StartingIntersectionPath;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Pathfinding")
	ASimplePath* StartingSimplePath;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Pathfinding")
	TArray<AIntersectionPath*> CurrentPath;
	
	bool bIsLastIntersection = false;
	bool bHasChicken = false;
	bool bGoParking = false;
	
	void CheckOverlappingPaths();
	void FollowPath(const TArray<AIntersectionPath*>& Path);
	void MoveToNextPoint();
	void OnReachDestination();
protected:
	virtual void BeginPlay() override;
};
