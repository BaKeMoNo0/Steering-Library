// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EBehaviorType.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"


//class UNCPMovementComponent;
class UInputMappingContext;

UCLASS()
class PROJECT_API APlayerCharacter : public ACharacter {
	GENERATED_BODY()


protected:
	virtual void BeginPlay() override;

public:
	UEBehaviorType CurrentBehavior;
	
	void SetBehavior(const UEBehaviorType NewBehavior);
};
