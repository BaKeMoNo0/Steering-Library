// Fill out your copyright notice in the Description page of Project Settings.


#include "Word/Spline/CircuitSpline.h"

#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter/NCPMovementComponent.h"


ACircuitSpline::ACircuitSpline() {
	PrimaryActorTick.bCanEverTick = true;
}


void ACircuitSpline::BeginPlay() {
	Super::BeginPlay();

	SplineComponent =  FindComponentByClass<USplineComponent>();
	NCPRef = Cast<ANPlayerCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), ANPlayerCharacter::StaticClass()));
	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerCharacter::StaticClass()));
}


void ACircuitSpline::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (SplineComponent && NCPRef  && (PlayerCharacter->NPCMovementComponent->CurrentBehavior == Circuit || PlayerCharacter->NPCMovementComponent->CurrentBehavior == OneWay || PlayerCharacter->NPCMovementComponent->CurrentBehavior == TwoWay)) {
		const int NumPoints = SplineComponent->GetNumberOfSplinePoints();
		for (int i = 0; i < NumPoints - 1; i++) {
			FVector Start = SplineComponent->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World);
			FVector End = SplineComponent->GetLocationAtSplinePoint(i + 1, ESplineCoordinateSpace::World);
			DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, -1, 0, 5.0f);
		}
		
		FVector	Start = SplineComponent->GetLocationAtSplinePoint(NumPoints - 1, ESplineCoordinateSpace::World);
		FVector	End = SplineComponent->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World);
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, -1, 0, 5.0f);
	}
}

