// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Engine/World.h"
#include "Kismet//GameplayStatics.h"
#include "TimerManager.h"
#include "DodgeballProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "LookAtActorComponent.h"


// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LookAtActorComponent = CreateDefaultSubobject<ULookAtActorComponent>(TEXT("Look At Actor Component"));
	LookAtActorComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Fetch the character currently being controlled by the player
	ACharacter* Playercharacter = UGameplayStatics::GetPlayerCharacter(this, 0);

	LookAtActorComponent->SetTarget(Playercharacter);
	
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Look at the player character every frame
	CanSeePlayer = LookAtActorComponent->CanSeeTarget();

	if (CanSeePlayer != PreviousCanSeePlayer) {
		if (CanSeePlayer) {
			// Start throwing dodgeball
			GetWorldTimerManager().SetTimer(ThrowTimerHandle, this, 
				&AEnemyCharacter::ThrowDodgeball, 
				ThrowingInterval, true, ThrowingDelay);
		}
		else {
			// Stop throwing dodgeball
			GetWorldTimerManager().ClearTimer(ThrowTimerHandle);
		}
	}

	PreviousCanSeePlayer = CanSeePlayer;

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// function to change the rotation of current sctor to face the given actor
/*bool AEnemyCharacter::LookAtActor(AActor* TargetActor)
{
	if (TargetActor == nullptr) {
		return false;
	}

	// declare array of actors to ignore
	const TArray<const AActor*> IgnoreActors = { this, TargetActor };

	// check if we can see actor
	if (UDodgeballFunctionLibrary::CanSeeActor(GetWorld(), 
		SightSource->GetComponentLocation(), TargetActor, IgnoreActors)) {

		FVector Start = GetActorLocation();
		FVector End = TargetActor->GetActorLocation();

		// Calculate the required rotation for the start point to face the end point 
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(Start, End);

		// Set the enemy's rotation to that rotation
		SetActorRotation(LookAtRotation);

		return true;
	}
	return false;
}*/

void AEnemyCharacter::ThrowDodgeball()
{
	if (DodgeballClass == nullptr) {
		return;
	}

	FVector ForwardVector = GetActorForwardVector();
	float SpawnDistance = 40.0f;
	FVector SpawnLocation = GetActorLocation() + (ForwardVector * SpawnDistance);

	FTransform SpawnTransform(GetActorRotation(), SpawnLocation);

	// Spawn new dodgeball
	ADodgeballProjectile* Projectile = GetWorld()->SpawnActorDeferred<ADodgeballProjectile>(DodgeballClass, SpawnTransform);

	// Change Projectile speed
	Projectile->GetProjectileMovementComponent()->InitialSpeed = 2200.0f;
	Projectile->FinishSpawning(SpawnTransform);
}

