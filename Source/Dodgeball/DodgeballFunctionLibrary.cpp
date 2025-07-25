// Fill out your copyright notice in the Description page of Project Settings.


#include "DodgeballFunctionLibrary.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"

bool UDodgeballFunctionLibrary::CanSeeActor(const UWorld* World, FVector Location, const AActor* TargetActor, TArray<const AActor*> IgnoreActors)
{
	if (TargetActor == nullptr) {
		return false;
	}
	// Store the results of the line trace
	FHitResult Hit;

	// Where the line trace starts and ends
	FVector Start = Location;
	FVector End = TargetActor->GetActorLocation();

	// The trace channel we want to compare against
	// Custom created trace channel in the editor
	ECollisionChannel Channel = ECollisionChannel::ECC_GameTraceChannel1;

	FCollisionQueryParams QueryParams;
	// Ignore the specified actors
	QueryParams.AddIgnoredActors(IgnoreActors);
	// Ignore the actor that's executing this line trace
	//QueryParams.AddIgnoredActor(this);
	// Ignore the target we're checking for
	//QueryParams.AddIgnoredActor(TargetActor);

	//Execute the line trace
	World->LineTraceSingleByChannel(Hit, Start, End, Channel, QueryParams);

	// show the line trace in the game
	//DrawDebugLine(World, Start, End, FColor::Red);

	return !Hit.bBlockingHit;
}
