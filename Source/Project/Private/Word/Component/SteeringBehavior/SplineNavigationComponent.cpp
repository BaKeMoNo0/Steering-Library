// Fill out your copyright notice in the Description page of Project Settings.


#include "Word/Component/SteeringBehavior/SplineNavigationComponent.h"
#include "EngineUtils.h"


void USplineNavigationComponent::BeginPlay() {
	Super::BeginPlay();
	
	if (!PathToFollow) {
		for (TActorIterator<ACircuitSpline> It(GetWorld()); It; ++It) {
			PathToFollow = *It;
			break;
		}
	}
}

FVector USplineNavigationComponent::GetNextTargetOnSpline(ANPlayerCharacter* NPC, int& CurrentIndex) {
	if (!PathToFollow) return FVector::ZeroVector;
	FVector TargetPosition = PathToFollow->SplineComponent->GetLocationAtSplinePoint(CurrentIndex, ESplineCoordinateSpace::World);
	return TargetPosition;
}


int USplineNavigationComponent::NearestSplinePoint(ANPlayerCharacter* NPC) {
	int Ind = 0;
	if (!PathToFollow || !PathToFollow->SplineComponent) return -2;
	int NumPoints = PathToFollow->SplineComponent->GetNumberOfSplinePoints();
	if (NumPoints == 0) return -2;
	FVector Point = PathToFollow->SplineComponent->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World);
	float DistanceToTarget = FVector::Dist(NPC->GetActorLocation(), Point);
	
	for (int i = 1; i < NumPoints; i++) {
		Point = PathToFollow->SplineComponent->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World);
		float DistanceToTarget2 = FVector::Dist(NPC->GetActorLocation(), Point);
		if (DistanceToTarget > DistanceToTarget2) {
			Ind = i;
			DistanceToTarget = DistanceToTarget2;
		}
	}
	return Ind;
}
