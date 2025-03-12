// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter/NCPMovementComponent.h"

#include "EngineUtils.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter/NPlayerCharacter.h"


UNCPMovementComponent::UNCPMovementComponent() {
	PrimaryComponentTick.bCanEverTick = true;
	MaxSpeed = 400.0f;
	MaxForce = 200.0f;
	Mass = 40.0f;
}


void UNCPMovementComponent::BeginPlay() {
	Super::BeginPlay();

	OwnerCharacter = Cast<APlayerCharacter>(GetOwner());
	NPCRef = Cast<ANPlayerCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), ANPlayerCharacter::StaticClass()));
	
	if (!PathToFollow) {
		for (TActorIterator<ACircuitSpline> It(GetWorld()); It; ++It) {
			PathToFollow = *It;
			break;
		}
	}
}


void UNCPMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (NPCRef) {
		FVector TargetLocation = OwnerCharacter->GetActorLocation();
		ExecuteCurrentBehavior(TargetLocation);
	}
}


void UNCPMovementComponent::SetBehavior(const UEBehaviorType NewBehavior){
	CurrentBehavior = NewBehavior;
}


void UNCPMovementComponent::ExecuteCurrentBehavior(FVector TargetLocation) {
	switch (CurrentBehavior) {
	case Walk:
		NPCRef->AddMovementInput(NPCRef->GetActorForwardVector(), 1.0f);
		break;
	case Seek:
		SeekBehavior(TargetLocation);
		break;
	case Flee:
		FleeBehavior(TargetLocation);
		break;
	case Pursuit:
		PursuitBehavior(TargetLocation);
		break;
	case Evade:
		EvadeBehavior(TargetLocation);
		break;
	case Arrival:
		ArrivalBehavior(TargetLocation);
		break;
	case Circuit:
		CircuitBehavior();
		break;
	case OneWay:
		OneWayBehavior();
		break;
	case TwoWay:
		TwoWayBehavior();
		break;
	default:
		break;
	}
}


FVector UNCPMovementComponent::CalculateSteeringForce(const FVector& DesiredVelocity) {
	if (Velocity == FVector::ZeroVector) Velocity = NPCRef->GetCharacterMovement()->Velocity;
	FVector CurrentVelocity = Velocity;
	FVector Steering = DesiredVelocity - CurrentVelocity;
	return Steering.GetClampedToMaxSize(MaxForce);
}


void UNCPMovementComponent::MoveWithSteering(const FVector& Steering) {
	FVector Acceleration = Steering / Mass;
	FVector NewVelocity = Velocity + Acceleration;
	NewVelocity = NewVelocity.GetClampedToMaxSize(MaxSpeed);
	Velocity = NewVelocity;
	FVector NewForward = NewVelocity.GetSafeNormal();
	NPCRef->AddMovementInput(NewForward, 1.0f);

	if (!NewVelocity.IsNearlyZero()) {
		FRotator NewRotation = NewVelocity.Rotation();
		NewRotation.Pitch = 0;
		NewRotation.Roll = 0;
		NPCRef->SetActorRotation(NewRotation);
	}
}


void UNCPMovementComponent::SeekBehavior(const FVector& Target) {
	FVector CurrentPosition = NPCRef->GetActorLocation();
	FVector DesiredVelocity = (Target - CurrentPosition).GetSafeNormal() * MaxSpeed;
	FVector Steering = CalculateSteeringForce(DesiredVelocity);
	MoveWithSteering(Steering);
}


void UNCPMovementComponent::FleeBehavior(const FVector& Target) {
	FVector CurrentPosition = NPCRef->GetActorLocation();
	FVector DesiredVelocity = (CurrentPosition - Target).GetSafeNormal() * MaxSpeed;
	FVector Steering = CalculateSteeringForce(DesiredVelocity);
	MoveWithSteering(Steering);
}


void UNCPMovementComponent::PursuitBehavior(const FVector& Target) {
	FVector CurrentPosition = NPCRef->GetActorLocation();
	FVector TargetVelocity = OwnerCharacter->GetVelocity();
	float DistanceToTarget = FVector::Dist(CurrentPosition, Target);

	FVector ToTarget = (Target - CurrentPosition).GetSafeNormal();
	float Alignment = FVector::DotProduct(ToTarget, TargetVelocity.GetSafeNormal());

	float c = FMath::Lerp(0.3f, 1.0f, 1.0f - (Alignment * 0.5f));

	float RelativeSpeed = (TargetVelocity - NPCRef->GetCharacterMovement()->Velocity).Size();
    float PredictionTime = (RelativeSpeed > 0) ? (DistanceToTarget / RelativeSpeed) * c : 0.5f;
    PredictionTime = FMath::Clamp(PredictionTime, 0.1f, 2.5f);
    FVector PredictedTarget = Target + TargetVelocity * PredictionTime;

	SeekBehavior(PredictedTarget);
}


void UNCPMovementComponent::EvadeBehavior(const FVector& Target) {
	FVector CurrentPosition = NPCRef->GetActorLocation();
	FVector TargetVelocity = OwnerCharacter->GetVelocity();
	float DistanceToTarget = FVector::Dist(CurrentPosition, Target);

	FVector ToTarget = (Target - CurrentPosition).GetSafeNormal();
	float Alignment = FVector::DotProduct(ToTarget, TargetVelocity.GetSafeNormal());

	float c = FMath::Lerp(0.3f, 1.0f, 1.0f - (Alignment * 0.5f));
	
	float RelativeSpeed = (TargetVelocity - NPCRef->GetCharacterMovement()->Velocity).Size();
	float PredictionTime = (RelativeSpeed > 0) ? (DistanceToTarget / RelativeSpeed) * c : 0.3f;
	PredictionTime = FMath::Clamp(PredictionTime, 0.1f, 2.5f);
	FVector PredictedTarget = Target + TargetVelocity * PredictionTime;

	FleeBehavior(PredictedTarget);
}


void UNCPMovementComponent::ArrivalBehavior(const FVector& Target) {
	FVector CurrentPosition = NPCRef->GetActorLocation();
	float DistanceToTarget = FVector::Dist(CurrentPosition, Target);
	float SlowingDistance = 200.0f;
	
	if (DistanceToTarget > SlowingDistance) {
		SeekBehavior(Target);
	} else {
		float RampedSpeed = MaxSpeed * (DistanceToTarget / SlowingDistance);
		float ClippedSpeed = FMath::Min(RampedSpeed, MaxSpeed);

		FVector DesiredVelocity = (Target - CurrentPosition).GetSafeNormal() * ClippedSpeed;

		float SpeedFactor = ClippedSpeed / MaxSpeed;
		FVector Steering = CalculateSteeringForce(DesiredVelocity);

		FVector Acceleration = Steering / Mass;
		FVector NewVelocity = Velocity + Acceleration;
		NewVelocity = NewVelocity.GetClampedToMaxSize(MaxSpeed);
		Velocity = NewVelocity;
	
		FVector NewForward = NewVelocity.GetSafeNormal();
		NPCRef->AddMovementInput(NewForward, SpeedFactor);

		if (!NewVelocity.IsNearlyZero()) {
			FRotator NewRotation = NewVelocity.Rotation();
			NewRotation.Pitch = 0;
			NewRotation.Roll = 0;
			NPCRef->SetActorRotation(NewRotation);
		}
	}
}


void UNCPMovementComponent::CircuitBehavior() {
	if (!PathToFollow) return;

	if (CurrentSplineIndex < 0) {
		CurrentSplineIndex = NearestSplinePoint();
	}
	
	FVector NextTarget = GetNextTargetOnSpline(CurrentSplineIndex);
	float DistanceToTarget = FVector::Dist(NPCRef->GetActorLocation(), NextTarget);

	if (DistanceToTarget < AcceptanceRadius) {
		CurrentSplineIndex = (CurrentSplineIndex + 1) % PathToFollow->SplineComponent->GetNumberOfSplinePoints();
	}

	SeekBehavior(NextTarget);
}


FVector UNCPMovementComponent::GetNextTargetOnSpline(int& CurrentIndex) {
	if (!PathToFollow) return FVector::ZeroVector;
	FVector TargetPosition = PathToFollow->SplineComponent->GetLocationAtSplinePoint(CurrentIndex, ESplineCoordinateSpace::World);
	return TargetPosition;
}


int UNCPMovementComponent::NearestSplinePoint() {
	int Ind = 0;
	int NumPoints = PathToFollow->SplineComponent->GetNumberOfSplinePoints();
	if (NumPoints == 0) return -2;
	FVector Point = PathToFollow->SplineComponent->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World);
	float DistanceToTarget = FVector::Dist(NPCRef->GetActorLocation(), Point);
	
	for (int i = 1; i < NumPoints; i++) {
		Point = PathToFollow->SplineComponent->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World);
		float DistanceToTarget2 = FVector::Dist(NPCRef->GetActorLocation(), Point);
		if (DistanceToTarget > DistanceToTarget2) {
			Ind = i;
			DistanceToTarget = DistanceToTarget2;
		}
	}
	return Ind;
}


void UNCPMovementComponent::OneWayBehavior() {
	if (!PathToFollow) return;

	if (CurrentSplineIndex < 0) {
		CurrentSplineIndex = NearestSplinePoint();
	}

	FVector Target = GetNextTargetOnSpline(CurrentSplineIndex);
	float DistanceToTarget = FVector::Dist(NPCRef->GetActorLocation(), Target);

	if (CurrentSplineIndex == PathToFollow->SplineComponent->GetNumberOfSplinePoints() - 1 && DistanceToTarget < AcceptanceRadius) {
		ArrivalBehavior(Target);
	} else {
		SeekBehavior(Target);
		if (DistanceToTarget < AcceptanceRadius) {
			CurrentSplineIndex++;
		}
	}
}


void UNCPMovementComponent::TwoWayBehavior() {
	if (!PathToFollow) return;

	if (CurrentSplineIndex < 0) {
		CurrentSplineIndex = NearestSplinePoint();
		bIsReversing = false;
	}

	FVector Target = GetNextTargetOnSpline(CurrentSplineIndex);
	float DistanceToTarget = FVector::Dist(NPCRef->GetActorLocation(), Target);
	
	if (DistanceToTarget < AcceptanceRadius) {
		if (CurrentSplineIndex == 0) {
			ArrivalBehavior(Target);
			bIsReversing = false;
			if (!NPCRef->GetVelocity().IsNearlyZero()) {
				return;
			}
		}
		else if (CurrentSplineIndex == PathToFollow->SplineComponent->GetNumberOfSplinePoints() - 1) {
			ArrivalBehavior(Target);
			bIsReversing = true;
			if (!NPCRef->GetVelocity().IsNearlyZero()) {
				return;
			}
		}
		CurrentSplineIndex += (bIsReversing ? -1 : 1);
	}
	SeekBehavior(Target);
}


