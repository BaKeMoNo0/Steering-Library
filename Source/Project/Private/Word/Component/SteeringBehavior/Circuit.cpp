// Fill out your copyright notice in the Description page of Project Settings.


#include "Word/Component/SteeringBehavior/Circuit.h"
#include "Word/Component/SteeringBehavior/Seek.h"
#include "Word/Component/SteeringBehavior/SplineNavigationComponent.h"


void UCircuit::ExecuteBehavior(ANPlayerCharacter* NPC) {
	if (!NPC->SplineComp || !NPC->SplineComp->PathToFollow) return;

	if (CurrentSplineIndex < 0) {
		CurrentSplineIndex = NPC->SplineComp->NearestSplinePoint(NPC);
	}
	
	FVector NextTarget = NPC->SplineComp->GetNextTargetOnSpline(NPC, CurrentSplineIndex);
	float DistanceToTarget = FVector::Dist(NPC->GetActorLocation(), NextTarget);

	if (DistanceToTarget < AcceptanceRadius) {
		CurrentSplineIndex = (CurrentSplineIndex + 1) % NPC->SplineComp->PathToFollow->SplineComponent->GetNumberOfSplinePoints();
	}

	if (NPC->SeekComp) {
		NPC->SeekComp->ExecuteBehavior(NPC, NextTarget);
	}
}
