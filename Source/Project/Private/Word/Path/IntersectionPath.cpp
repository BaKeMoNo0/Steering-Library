// Fill out your copyright notice in the Description page of Project Settings.


#include "Word/Path/IntersectionPath.h"

#include "Components/BoxComponent.h"


AIntersectionPath::AIntersectionPath() {}


void AIntersectionPath::BeginPlay() {
	Super::BeginPlay();
}

void AIntersectionPath::GetAllNeighbors() {
	TArray<UBoxComponent*> BoxComponents;
	GetComponents<UBoxComponent>(BoxComponents);

	for (UBoxComponent* BoxComp : BoxComponents) {
		if (BoxComp && BoxComp->ComponentHasTag(FName("Path"))) {
			TArray<AActor*> OverlappingActors;
			BoxComp->GetOverlappingActors(OverlappingActors);
			if (OverlappingActors.Num() > 0){
				for (AActor* Actor : OverlappingActors) {
					ASimplePath* Path = Cast<ASimplePath>(Actor);
					if (Path) {
						ConnectedPaths.Add(Path);
						Path->ConnectedIntersectionPaths.Add(this);
					}
				}
			}
		}
	}
	//DebugLine();
}


void AIntersectionPath::DebugLine() {
	FColor Color = FColor::MakeRandomColor();
	if (ConnectedPaths.Num() > 0) {
		for (ASimplePath* Path : ConnectedPaths){
			FVector Location = FVector(GetActorLocation().X, GetActorLocation().Y, 50.0f);
			FVector Location2 = FVector(Path->GetActorLocation().X, Path->GetActorLocation().Y, 50.0f);
			DrawDebugLine(GetWorld(), Location, Location2, Color, true, 100.0f, 0, 50.0);
		}
	}
}


