// Fill out your copyright notice in the Description page of Project Settings.


#include "Word/Component/SteeringBehavior/TwoWay.h"

#include "Word/Component/SteeringBehavior/Arrival.h"
#include "Word/Component/SteeringBehavior/Seek.h"
#include "Word/Component/SteeringBehavior/SplineNavigationComponent.h"


void UTwoWay::ExecuteBehavior(ACharacter* NPC, USeek* SeekComp, USplineNavigationComponent* SplineComp, USteeringComponent* SteeringComp, UArrival* ArrivalComp) {
	if (!SplineComp->PathToFollow) return;

	if (CurrentSplineIndex < 0) {
		CurrentSplineIndex = SplineComp->NearestSplinePoint(NPC);
		bIsReversing = false;
	}

	FVector Target = SplineComp->GetNextTargetOnSpline(NPC, CurrentSplineIndex);
	float DistanceToTarget = FVector::Dist(NPC->GetActorLocation(), Target);
	
	if (DistanceToTarget < AcceptanceRadius) {
		if (CurrentSplineIndex == 0) {
			ArrivalComp->ExecuteBehavior(NPC, Target, SteeringComp, SeekComp);
			bIsReversing = false;
			if (!NPC->GetVelocity().IsNearlyZero()) {
				return;
			}
		}
		else if (CurrentSplineIndex == SplineComp->PathToFollow->SplineComponent->GetNumberOfSplinePoints() - 1) {
			ArrivalComp->ExecuteBehavior(NPC, Target, SteeringComp, SeekComp);
			bIsReversing = true;
			if (!NPC->GetVelocity().IsNearlyZero()) {
				return;
			}
		}
		CurrentSplineIndex += (bIsReversing ? -1 : 1);
	}
	SeekComp->ExecuteBehavior(NPC, Target, SteeringComp);
}
