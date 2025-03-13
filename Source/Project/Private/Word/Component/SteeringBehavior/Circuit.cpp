// Fill out your copyright notice in the Description page of Project Settings.


#include "Word/Component/SteeringBehavior/Circuit.h"
#include "Word/Component/SteeringBehavior/Seek.h"
#include "Word/Component/SteeringBehavior/SplineNavigationComponent.h"


void UCircuit::ExecuteBehavior(ACharacter* NPC, USeek* SeekComp, USplineNavigationComponent* SplineComp, USteeringComponent* SteeringComp) {
	if (!SplineComp || !SplineComp->PathToFollow) return;

	if (CurrentSplineIndex < 0) {
		CurrentSplineIndex = SplineComp->NearestSplinePoint(NPC);
	}
	
	FVector NextTarget = SplineComp->GetNextTargetOnSpline(NPC, CurrentSplineIndex);
	float DistanceToTarget = FVector::Dist(NPC->GetActorLocation(), NextTarget);

	if (DistanceToTarget < AcceptanceRadius) {
		CurrentSplineIndex = (CurrentSplineIndex + 1) % SplineComp->PathToFollow->SplineComponent->GetNumberOfSplinePoints();
	}
	SeekComp->ExecuteBehavior(NPC, NextTarget, SteeringComp);
}
