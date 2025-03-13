// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerCharacter/NPlayerCharacter.h"
#include "SteeringComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_API USteeringComponent : public UActorComponent {
	GENERATED_BODY()

public:
	FVector CalculateSteeringForce(ANPlayerCharacter* NPC, const FVector& DesiredVelocity);
	void MoveWithSteering(ANPlayerCharacter* NPC, const FVector& Steering);

	FVector Velocity = FVector::ZeroVector;
	float MaxSpeed = 400.0f;
	float MaxForce = 200.0f;
	float Mass = 40.0f;
};
