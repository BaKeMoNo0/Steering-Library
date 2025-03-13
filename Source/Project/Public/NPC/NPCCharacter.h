// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPC_AIController.h"
#include "GameFramework/Character.h"
#include "Word/Path/SimplePath.h"
#include "NPCCharacter.generated.h"

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
	UPathFindingManager* PathFindingManager;
	UPROPERTY()
	USeek* SeekComp;
	UPROPERTY()
	USteeringComponent* SteeringComp;
	UPROPERTY()
	ANPC_AIController* AIController;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Pathfinding")
	AIntersectionPath* StartingIntersectionPath;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Pathfinding")
	ASimplePath* StartingSimplePath;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Pathfinding")
	TArray<AIntersectionPath*> CurrentPath;
	bool bIsMoving = false;
	
	void CheckOverlappingPaths();
	void FollowPath(const TArray<AIntersectionPath*>& Path);
	void MoveToNextPoint();
	void OnReachDestination();
	void UpdatePath(const TArray<AIntersectionPath*>& NewPath);
	void MoveToTarget(FVector TargetPosition);
protected:
	virtual void BeginPlay() override;
};
