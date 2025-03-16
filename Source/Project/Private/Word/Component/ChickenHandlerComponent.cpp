// Fill out your copyright notice in the Description page of Project Settings.


#include "Word/Component/ChickenHandlerComponent.h"

#include "GameModeLab2.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Word/Component/PathFindingManager.h"


void UChickenHandlerComponent::BeginPlay() {
	Super::BeginPlay();
	OwnerCharacter = Cast<ANPCCharacter>(GetOwner());
	Fence = UGameplayStatics::GetActorOfClass(GetWorld(), FenceClass);
}


void UChickenHandlerComponent::PickupChicken(ANPCCharacter* Chicken) {
	if (!Chicken) return;

	Chicken->SetActorEnableCollision(false);
	Chicken->GetMesh()->SetSimulatePhysics(false);

	Chicken->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("ChickenSocket"));
	OwnerCharacter->bHasChicken = true;
	OwnerCharacter->GameModeLab2->ChickensTargets.Remove(Chicken);
}


void UChickenHandlerComponent::DropChicken(ANPCCharacter* CarriedChicken) {
	if (!CarriedChicken || !OwnerCharacter || !Fence) return;
	
	UBoxComponent* BoxComponent = Fence->FindComponentByClass<UBoxComponent>();
	if (!BoxComponent) return;

	FVector BoxOrigin = BoxComponent->GetComponentLocation();
	FVector BoxExtent = BoxComponent->GetScaledBoxExtent();
	
	FVector RandomLocation = FVector(
		FMath::RandRange(BoxOrigin.X - BoxExtent.X, BoxOrigin.X + BoxExtent.X),
		FMath::RandRange(BoxOrigin.Y - BoxExtent.Y, BoxOrigin.Y + BoxExtent.Y),
		BoxOrigin.Z
	);

	CarriedChicken->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	CarriedChicken->SetActorLocation(RandomLocation);
	CarriedChicken->SetActorEnableCollision(true);
	CarriedChicken->GetMesh()->SetSimulatePhysics(true);
	OwnerCharacter->bHasChicken = false;
	OwnerCharacter->PathFindingManager->ChickenTarget = nullptr;
}


bool UChickenHandlerComponent::IsOtherFarmersCloseToTarget(ANPCCharacter* TargetChicken) {
	if (!TargetChicken) return false;
	
	/*float Distance = FVector::Dist(OwnerCharacter->GameModeLab2->PlayerCharacter->GetActorLocation(), TargetChicken->GetActorLocation());
	if (Distance < 600.0f) {
		return true;
	}*/
	for (ANPCCharacter* OtherFarmer : OwnerCharacter->PathFindingManager->Farmers) {
		if (OtherFarmer != OwnerCharacter && OtherFarmer->PathFindingManager->ChickenTarget == TargetChicken) {
			float Dist = FVector::Dist(OtherFarmer->GetActorLocation(), TargetChicken->GetActorLocation());

			if (Dist < 600.f) {
				return true;
			}
		}
	}
	
	return false;
}

