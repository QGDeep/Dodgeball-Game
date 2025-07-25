// Fill out your copyright notice in the Description page of Project Settings.


#include "MusicActor.h"
#include "Components/AudioComponent.h"

// Sets default values
AMusicActor::AMusicActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Music Component"));

}

// Called when the game starts or when spawned
void AMusicActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMusicActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

