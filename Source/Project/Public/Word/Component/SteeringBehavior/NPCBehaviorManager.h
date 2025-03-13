// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerCharacter/NPlayerCharacter.h"
#include "PlayerCharacter/PlayerCharacter.h"
#include "NPCBehaviorManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_API UNPCBehaviorManager : public UActorComponent {
	GENERATED_BODY()
	void ExecuteCurrentBehavior(FVector TargetLocation);

public:
	UNPCBehaviorManager();	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY()
	APlayerCharacter* PlayerRef;
	UPROPERTY()
	ANPlayerCharacter* OwnerCharacter;

	
protected:
	virtual void BeginPlay() override;
};
