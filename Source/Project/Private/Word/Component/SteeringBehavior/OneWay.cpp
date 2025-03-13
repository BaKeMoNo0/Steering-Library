// Fill out your copyright notice in the Description page of Project Settings.


#include "Word/Component/SteeringBehavior/OneWay.h"

#include "Word/Component/SteeringBehavior/Arrival.h"
#include "Word/Component/SteeringBehavior/Seek.h"
#include "Word/Component/SteeringBehavior/SplineNavigationComponent.h"


void UOneWay::ExecuteBehavior(ANPlayerCharacter* NPC) {
	if (!NPC->SplineComp->PathToFollow) return;

	if (CurrentSplineIndex < 0) {
		CurrentSplineIndex = NPC->SplineComp->NearestSplinePoint(NPC);
	}

	FVector Target = NPC->SplineComp->GetNextTargetOnSpline(NPC, CurrentSplineIndex);
	float DistanceToTarget = FVector::Dist(NPC->GetActorLocation(), Target);

	if (CurrentSplineIndex == NPC->SplineComp->PathToFollow->SplineComponent->GetNumberOfSplinePoints() - 1 && DistanceToTarget < AcceptanceRadius) {
		NPC->ArrivalComp->ExecuteBehavior(NPC, Target);
	} else {
		NPC->SeekComp->ExecuteBehavior(NPC, Target);
		if (DistanceToTarget < AcceptanceRadius) {
			CurrentSplineIndex++;
		}
	}
}
