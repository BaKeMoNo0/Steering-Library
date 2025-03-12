// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/NPCCharacter.h"

#include "Components/BoxComponent.h"
#include "Word/Component/PathFindingManager.h"
#include "Word/Path/IntersectionPath.h"


ANPCCharacter::ANPCCharacter() {
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);

	CollisionBox->SetBoxExtent(FVector(10.f, 10.f, 10.f));

	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionBox->SetCollisionObjectType(ECC_WorldDynamic);
	CollisionBox->SetCollisionResponseToAllChannels(ECR_Overlap);
	CollisionBox->SetGenerateOverlapEvents(true);
	CollisionBox->bMultiBodyOverlap = true;

	AIControllerClass = ANPC_AIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}


void ANPCCharacter::BeginPlay() {
	Super::BeginPlay();

	PathFindingManager = FindComponentByClass<UPathFindingManager>();
	AIController = Cast<ANPC_AIController>(GetController());
}


void ANPCCharacter::CheckOverlappingPaths() {
	if (CollisionBox) {
		FVector BoxExtent = CollisionBox->GetScaledBoxExtent();
		FVector BoxCenter = CollisionBox->GetComponentLocation();

		DrawDebugBox(GetWorld(), BoxCenter, BoxExtent, FColor::Yellow, true, 10.0f);
		
		TArray<AActor*> OverlappingActors;
		CollisionBox->GetOverlappingActors(OverlappingActors);
        
		for (AActor* Actor : OverlappingActors) {
			if (Actor->IsA(ASimplePath::StaticClass())) {
				StartingSimplePath = Cast<ASimplePath>(Actor);
				StartingIntersectionPath = StartingSimplePath->GetStartIntersection();
			}
			else if (Actor->IsA(AIntersectionPath::StaticClass())) {
				StartingIntersectionPath = Cast<AIntersectionPath>(Actor);
			}
		}
	}
}


void ANPCCharacter::FollowPath(const TArray<AIntersectionPath*>& Path) {
	if (Path.Num() == 0) return;
    
	CurrentPathIndex = 0;
	CurrentPath = Path;

	MoveToNextPoint();
}


void ANPCCharacter::MoveToNextPoint() {
	if (CurrentPathIndex >= CurrentPath.Num()) return;

	AIntersectionPath* NextPoint = CurrentPath[CurrentPathIndex];
	if (!NextPoint) return;
	if (AIController) {
		FVector Location = FVector(NextPoint->GetActorLocation().X, NextPoint->GetActorLocation().Y, 140.0f);
		AIController->MoveToTarget(Location);
	}
}


void ANPCCharacter::OnReachDestination() {
	CurrentPathIndex++;

	if (CurrentPathIndex < CurrentPath.Num()) {
		MoveToNextPoint();
	}
}


void ANPCCharacter::UpdatePath(const TArray<AIntersectionPath*>& NewPath) {
	if (NewPath.Num() == 0) return;
    
	FollowPath(NewPath);
}