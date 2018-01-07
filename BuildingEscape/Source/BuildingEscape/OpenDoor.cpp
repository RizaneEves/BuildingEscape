// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Door = GetOwner();

	
}

void UOpenDoor::OpenDoor()
{
	//Door->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
	OnOpen.Broadcast();
}

void UOpenDoor::CloseDoor()
{
	//Door->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
	OnClose.Broadcast();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetTotalMassOnPlate() >= ThresholdMass)
	{
		OpenDoor();
	}
	else
	{
		CloseDoor();
	}

}

float UOpenDoor::GetTotalMassOnPlate()
{
	float TotalMass = 0.f;
	if (!PressurePlate) return TotalMass;

	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	for (const auto& Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}

