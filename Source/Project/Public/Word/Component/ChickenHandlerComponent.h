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
	UPROPERTY()
	ANPCCharacter* OwnerCharacter;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> FenceClass;
	UPROPERTY()
	AActor* Fence;

	void PickupChicken(ANPCCharacter* Chicken);
	void DropChicken(ANPCCharacter* CarriedChicken);

protected:
	virtual void BeginPlay() override;

};
