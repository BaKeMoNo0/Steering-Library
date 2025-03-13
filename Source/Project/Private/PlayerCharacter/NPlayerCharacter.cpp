// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter/NPlayerCharacter.h"
#include "Word/Component/SteeringBehavior/Arrival.h"
#include "Word/Component/SteeringBehavior/Circuit.h"
#include "Word/Component/SteeringBehavior/Evade.h"
#include "Word/Component/SteeringBehavior/Flee.h"
#include "Word/Component/SteeringBehavior/NPCBehaviorManager.h"
#include "Word/Component/SteeringBehavior/OneWay.h"
#include "Word/Component/SteeringBehavior/Pursuit.h"
#include "Word/Component/SteeringBehavior/Seek.h"
#include "Word/Component/SteeringBehavior/SplineNavigationComponent.h"
#include "Word/Component/SteeringBehavior/SteeringComponent.h"
#include "Word/Component/SteeringBehavior/TwoWay.h"


void ANPlayerCharacter::BeginPlay() {
	Super::BeginPlay();
	BehaviorManagerComp = FindComponentByClass<UNPCBehaviorManager>();
	SteeringComp = FindComponentByClass<USteeringComponent>(); 
	SeekComp = FindComponentByClass<USeek>();
	FleeComp = FindComponentByClass<UFlee>();
	PursuitComp = FindComponentByClass<UPursuit>();
	EvadeComp = FindComponentByClass<UEvade>();
	ArrivalComp = FindComponentByClass<UArrival>();
	SplineComp = FindComponentByClass<USplineNavigationComponent>();
	CircuitComp = FindComponentByClass<UCircuit>();
	OneWayComp = FindComponentByClass<UOneWay>();
	TwoWayComp = FindComponentByClass<UTwoWay>();
}