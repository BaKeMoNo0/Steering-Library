// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NPC/NPCCharacter.h"
#include "ChickenHandlerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_API UChickenHandlerComponent : public UActorComponent {
	GENERATED_BODY()

public:
	UChickenHandlerComponent();
	
	UPROPERTY()
	ANPCCharacter* OwnerCharacter;

	void PickupChicken(ANPCCharacter* Chicken);

protected:
	virtual void BeginPlay() override;

};
