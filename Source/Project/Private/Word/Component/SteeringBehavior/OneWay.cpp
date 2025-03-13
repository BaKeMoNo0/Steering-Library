// Fill out your copyright notice in the Description page of Project Settings.


#include "Word/Component/SteeringBehavior/OneWay.h"

#include "Word/Component/SteeringBehavior/Arrival.h"
#include "Word/Component/SteeringBehavior/Seek.h"
#include "Word/Component/SteeringBehavior/SplineNavigationComponent.h"


void UOneWay::ExecuteBehavior(ACharacter* NPC, USeek* SeekComp, USplineNavigationComponent* SplineComp, USteeringComponent* SteeringComp,  UArrival* ArrivalComp) {
	if (!SplineComp->PathToFollow) return;

	if (CurrentSplineIndex < 0) {
		CurrentSplineIndex = SplineComp->NearestSplinePoint(NPC);
	}

	FVector Target = SplineComp->GetNextTargetOnSpline(NPC, CurrentSplineIndex);
	float DistanceToTarget = FVector::Dist(NPC->GetActorLocation(), Target);

	if (CurrentSplineIndex == SplineComp->PathToFollow->SplineComponent->GetNumberOfSplinePoints() - 1 && DistanceToTarget < AcceptanceRadius) {
		ArrivalComp->ExecuteBehavior(NPC, Target, SteeringComp, SeekComp);
	} else {
		SeekComp->ExecuteBehavior(NPC, Target, SteeringComp);
		if (DistanceToTarget < AcceptanceRadius) {
			CurrentSplineIndex++;
		}
	}
}
