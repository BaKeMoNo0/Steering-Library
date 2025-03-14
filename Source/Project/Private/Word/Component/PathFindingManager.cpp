// Fill out your copyright notice in the Description page of Project Settings.


#include "Word/Component/PathFindingManager.h"


void UPathFindingManager::BeginPlay() {
	Super::BeginPlay();

    OwnerCharacter = Cast<ANPCCharacter>(GetOwner());
}


TArray<AIntersectionPath*> UPathFindingManager::Dijkstra(AIntersectionPath* StartPath, AIntersectionPath* TargetPath) {
    if (!StartPath || !TargetPath) return TArray<AIntersectionPath*>();
    
    // Init
    TMap<AIntersectionPath*, float> Distances;
    TMap<AIntersectionPath*, AIntersectionPath*> Predecessors;
    TArray<AIntersectionPath*> UnvisitedNodes;
    
    for (AIntersectionPath* Inter : AllIntersections) {
        if (Inter) {
            Distances.Add(Inter, FLT_MAX);
            Predecessors.Add(Inter, nullptr);
            UnvisitedNodes.Add(Inter);
        }
    }

    Distances[StartPath] = 0.0f;
    
    // Start Dijkstra
    while (UnvisitedNodes.Num() > 0) {
        AIntersectionPath* CurrentNode = nullptr;
        float MinDistance = FLT_MAX;

        for (AIntersectionPath* Node : UnvisitedNodes) {
            if (Distances[Node] < MinDistance) {
                MinDistance = Distances[Node];
                CurrentNode = Node;
            }
        }
        if (!CurrentNode) break;
        UnvisitedNodes.Remove(CurrentNode);

        if (CurrentNode == TargetPath) {
            break;
        }
        
        // Update neighbor distances
        for (ASimplePath* Path : CurrentNode->ConnectedPaths) {
            AIntersectionPath* Neighbor = Path->GetOtherIntersection(CurrentNode);
            if (Neighbor) {
                float NewDistance = Distances[CurrentNode] + Path->GetCost();
                if (NewDistance < Distances[Neighbor]) {
                    Distances[Neighbor] = NewDistance;
                    Predecessors[Neighbor] = CurrentNode;
                }
            }
        }
    }

    // Rebuild the path from the best target
    TArray<AIntersectionPath*> ShortestPath;
    AIntersectionPath* Current = TargetPath;
    while (Current) {
        if (Current == OwnerCharacter->FarmIntersection && OwnerCharacter->StartingIntersectionPath == OwnerCharacter->FarmIntersection) {
            Current = Predecessors[Current];
            continue;
        }
        ShortestPath.Insert(Current, 0);
        Current = Predecessors[Current];
    }
    return ShortestPath;
}


TArray<AIntersectionPath*> UPathFindingManager::FindPathToClosestChicken() {
    if (ChickensTargets.Num() == 0) return TArray<AIntersectionPath*>();

    AIntersectionPath* StartPath = OwnerCharacter->StartingIntersectionPath;
    if (!StartPath) return TArray<AIntersectionPath*>();

    AIntersectionPath* BestTargetPath = nullptr;
    float BestCost = FLT_MAX;

    for (ANPCCharacter* Chicken : ChickensTargets) {
        if (Chicken && Chicken->StartingIntersectionPath) {
            TArray<AIntersectionPath*> Path = Dijkstra(StartPath, Chicken->StartingIntersectionPath);
            float PathCost = Path.Num();

            if (PathCost > 0 && PathCost < BestCost) {
                BestCost = PathCost;
                BestTargetPath = Chicken->StartingIntersectionPath;
                ChickenTarget = Chicken;
            }
        }
    }

    if (!BestTargetPath) return TArray<AIntersectionPath*>();  

    return Dijkstra(StartPath, BestTargetPath);
}


void UPathFindingManager::MoveToIntersection(TArray<AIntersectionPath*> Path) {
    if (OwnerCharacter && Path.Num() > 0) {
        OwnerCharacter->FollowPath(Path);
    }
}


void UPathFindingManager::MoveToChickenPosition(FVector TargetPosition) {
    if (OwnerCharacter->AIController) {
        OwnerCharacter->bIsLastIntersection = true;
        OwnerCharacter->AIController->MoveToTarget(TargetPosition);
    }
}


void UPathFindingManager::RecalculatePath() {
    OwnerCharacter->CheckOverlappingPaths();
    if (OwnerCharacter->StartingIntersectionPath != OwnerCharacter->FarmIntersection) {
        TArray<AIntersectionPath*> NewPath = Dijkstra(OwnerCharacter->StartingIntersectionPath, OwnerCharacter->FarmIntersection);
        for (AIntersectionPath* Path : NewPath)
        {
            UE_LOG(LogTemp, Warning, TEXT("Recalculating Path : %s"), *Path->GetPathName());
        }
        MoveToIntersection(NewPath);
    }
}

