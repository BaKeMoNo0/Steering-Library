// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimplePath.generated.h"


class AIntersectionPath;

UCLASS()
class PROJECT_API ASimplePath : public AActor {
	GENERATED_BODY()
	
public:
	ASimplePath();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY()
	float Cost = 1.0f;

	UPROPERTY()
	AIntersectionPath* StartIntersection;

	UPROPERTY()
	AIntersectionPath* EndIntersection;

public:
	UPROPERTY(BlueprintReadWrite, Category="Paths")
	TArray<AIntersectionPath*> ConnectedIntersectionPaths;
	
	void InitializeIntersections();
	float GetCost() const { return Cost; }
	AIntersectionPath* GetStartIntersection() { return StartIntersection; }
	AIntersectionPath* GetEndIntersection() { return EndIntersection; }
	AIntersectionPath* GetOtherIntersection(AIntersectionPath* From);
};
