// Fill out your copyright notice in the Description page of Project Settings.


#include "Word/Component/SteeringBehavior/TwoWay.h"

#include "Word/Component/SteeringBehavior/Arrival.h"
#include "Word/Component/SteeringBehavior/Seek.h"
#include "Word/Component/SteeringBehavior/SplineNavigationComponent.h"


void UTwoWay::ExecuteBehavior(ANPlayerCharacter* NPC) {
	if (!NPC->SplineComp->PathToFollow) return;

	if (CurrentSplineIndex < 0) {
		CurrentSplineIndex = NPC->SplineComp->NearestSplinePoint(NPC);
		bIsReversing = false;
	}

	FVector Target = NPC->SplineComp->GetNextTargetOnSpline(NPC, CurrentSplineIndex);
	float DistanceToTarget = FVector::Dist(NPC->GetActorLocation(), Target);
	
	if (DistanceToTarget < AcceptanceRadius) {
		if (CurrentSplineIndex == 0) {
			NPC->ArrivalComp->ExecuteBehavior(NPC, Target);
			bIsReversing = false;
			if (!NPC->GetVelocity().IsNearlyZero()) {
				return;
			}
		}
		else if (CurrentSplineIndex == NPC->SplineComp->PathToFollow->SplineComponent->GetNumberOfSplinePoints() - 1) {
			NPC->ArrivalComp->ExecuteBehavior(NPC, Target);
			bIsReversing = true;
			if (!NPC->GetVelocity().IsNearlyZero()) {
				return;
			}
		}
		CurrentSplineIndex += (bIsReversing ? -1 : 1);
	}
	NPC->SeekComp->ExecuteBehavior(NPC, Target);
}
