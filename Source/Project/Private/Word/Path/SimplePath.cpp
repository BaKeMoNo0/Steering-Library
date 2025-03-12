// Fill out your copyright notice in the Description page of Project Settings.


#include "Word/Path/SimplePath.h"

#include "Word/Path/IntersectionPath.h"

ASimplePath::ASimplePath() {}


void ASimplePath::BeginPlay() {
	Super::BeginPlay();
}


void ASimplePath::InitializeIntersections() {
	if (ConnectedIntersectionPaths.Num() >= 2) {
		StartIntersection = ConnectedIntersectionPaths[0];
		EndIntersection = ConnectedIntersectionPaths[1];
	} 
	else if (ConnectedIntersectionPaths.Num() == 1) {
		StartIntersection = ConnectedIntersectionPaths[0];
		EndIntersection = nullptr;
	}

	if (StartIntersection && EndIntersection) {
		Cost = FVector::Dist(StartIntersection->GetActorLocation(), EndIntersection->GetActorLocation());
	}
}

AIntersectionPath* ASimplePath::GetOtherIntersection(AIntersectionPath* From) {
	if (!StartIntersection || !EndIntersection) return nullptr;
	return (From == StartIntersection) ? EndIntersection : StartIntersection;
}


