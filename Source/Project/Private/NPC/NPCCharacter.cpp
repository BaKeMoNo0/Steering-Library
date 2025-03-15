// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/NPCCharacter.h"

#include "GameModeLab2.h"
#include "Components/BoxComponent.h"
#include "Word/Component/ChickenHandlerComponent.h"
#include "Word/Component/PathFindingManager.h"
#include "Word/Component/SteeringBehavior/Arrival.h"
#include "Word/Component/SteeringBehavior/Seek.h"
#include "Word/Component/SteeringBehavior/SteeringComponent.h"
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

	AIController = Cast<ANPC_AIController>(GetController());
	PathFindingManager = FindComponentByClass<UPathFindingManager>();
	SeekComp = FindComponentByClass<USeek>();
	SteeringComp = FindComponentByClass<USteeringComponent>();
	ChickenHandler = FindComponentByClass<UChickenHandlerComponent>();
	ArrivalComp = FindComponentByClass<UArrival>();
	//PlannerComp = FindComponentByClass<UPlannerComponent>();
	GameModeLab2 = Cast<AGameModeLab2>(GetWorld()->GetAuthGameMode());
}


void ANPCCharacter::CheckOverlappingPaths() {
	if (CollisionBox) {
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
	bIsLastIntersection = false;

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
	else if (CurrentPathIndex == CurrentPath.Num() && PathFindingManager->ChickenTarget) {
		PathFindingManager->MoveToPosition(PathFindingManager->ChickenTarget->GetActorLocation());
	}
}
