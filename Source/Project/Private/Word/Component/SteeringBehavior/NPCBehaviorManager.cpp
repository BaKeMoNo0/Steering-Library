// Fill out your copyright notice in the Description page of Project Settings.


#include "Word/Component/SteeringBehavior/NPCBehaviorManager.h"
#include "Kismet/GameplayStatics.h"
#include "Word/Component/SteeringBehavior/Arrival.h"
#include "Word/Component/SteeringBehavior/Circuit.h"
#include "Word/Component/SteeringBehavior/Evade.h"
#include "Word/Component/SteeringBehavior/Flee.h"
#include "Word/Component/SteeringBehavior/OneWay.h"
#include "Word/Component/SteeringBehavior/Pursuit.h"
#include "Word/Component/SteeringBehavior/Seek.h"
#include "Word/Component/SteeringBehavior/TwoWay.h"


UNPCBehaviorManager::UNPCBehaviorManager() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UNPCBehaviorManager::BeginPlay() {
	Super::BeginPlay();

	OwnerCharacter = Cast<ANPlayerCharacter>(GetOwner());
	PlayerRef = Cast<APlayerCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerCharacter::StaticClass()));
}


void UNPCBehaviorManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (OwnerCharacter && PlayerRef) {
		FVector TargetLocation = PlayerRef->GetActorLocation();
		ExecuteCurrentBehavior(TargetLocation);
	}
}


void UNPCBehaviorManager::ExecuteCurrentBehavior(FVector TargetLocation) {
	switch (PlayerRef->CurrentBehavior) {
	case Walk:
		OwnerCharacter->AddMovementInput(OwnerCharacter->GetActorForwardVector(), 1.0f);
		break;
	case Seek:
		OwnerCharacter->SeekComp->ExecuteBehavior(OwnerCharacter, TargetLocation);
		break;
	case Flee:
		OwnerCharacter->FleeComp->ExecuteBehavior(OwnerCharacter, TargetLocation);
		break;
	case Pursuit:
		OwnerCharacter->PursuitComp->ExecuteBehavior(OwnerCharacter, TargetLocation, PlayerRef);
		break;
	case Evade:
		OwnerCharacter->EvadeComp->ExecuteBehavior(OwnerCharacter, TargetLocation, PlayerRef);
		break;
	case Arrival:
		OwnerCharacter->ArrivalComp->ExecuteBehavior(OwnerCharacter, TargetLocation);
		break;
	case Circuit:
		OwnerCharacter->CircuitComp->ExecuteBehavior(OwnerCharacter);
		break;
	case OneWay:
		OwnerCharacter->OneWayComp->ExecuteBehavior(OwnerCharacter);
		break;
	case TwoWay:
		OwnerCharacter->TwoWayComp->ExecuteBehavior(OwnerCharacter);
		break;
	default:
		break;
	}
}

