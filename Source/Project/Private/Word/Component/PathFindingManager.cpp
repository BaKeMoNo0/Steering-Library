// Fill out your copyright notice in the Description page of Project Settings.


#include "Word/Component/PathFindingManager.h"

UPathFindingManager::UPathFindingManager() {}



void UPathFindingManager::BeginPlay() {
	Super::BeginPlay();

    if (!OwnerCharacter) OwnerCharacter = Cast<ANPCCharacter>(GetOwner());
}


TArray<AIntersectionPath*> UPathFindingManager::Dijkstra() {
    AIntersectionPath* StartPath = OwnerCharacter->StartingIntersectionPath;
    if (!StartPath || ChickensTargets.Num() == 0) return TArray<AIntersectionPath*>();
    
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

    TArray<AIntersectionPath*> BestTargets;
    float BestCost = FLT_MAX;
    
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
        
        for (ANPCCharacter* TargetChicken : ChickensTargets) {
            if (TargetChicken && TargetChicken->StartingIntersectionPath == CurrentNode) {
                float TargetCost = Distances[CurrentNode];
                if (TargetCost < BestCost) {
                    BestCost = TargetCost;
                    BestTargets.Empty();
                    BestTargets.Add(CurrentNode);
                    CurrentNode->ChickenTarget = TargetChicken;
                }
                else if (TargetCost == BestCost) {
                    BestTargets.Add(CurrentNode);
                }
            }
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
    if (BestTargets.Num() == 0) return TArray<AIntersectionPath*>();

    AIntersectionPath* FinalTarget = BestTargets[0];
    for (AIntersectionPath* Target : BestTargets) {
        if (Distances[Target] < Distances[FinalTarget]) {
            FinalTarget = Target;
        }
    }

    // Rebuild the path from the best target
    TArray<AIntersectionPath*> ShortestPath;
    AIntersectionPath* Current = FinalTarget;
    while (Current) {
        ShortestPath.Insert(Current, 0);  
        Current = Predecessors[Current];
    }
    return ShortestPath;
}


void UPathFindingManager::MoveToTarget(ANPCCharacter* NPC) {
    if (!NPC) return;
    TArray<AIntersectionPath*> Path = Dijkstra();
    if (Path.Num() > 0) {
        NPC->FollowPath(Path);
    }
}


void UPathFindingManager::RecalculatePath(ANPCCharacter* NPC) {
    if (!NPC) return;
    
    TArray<AIntersectionPath*> NewPath = Dijkstra();
    if (NewPath.Num() > 0) {
        NPC->UpdatePath(NewPath);
    }
}