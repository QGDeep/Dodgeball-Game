// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class DODGEBALL_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = LookAt, meta = (AllowPrivateAccess = "true"))
	class ULookAtActorComponent* LookAtActorComponent;

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// The class used to spawn a dodgeball object
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Dodgeball)
	TSubclassOf<class ADodgeballProjectile> DodgeballClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Change rotation of the actor to face the given actor
	// Return whether the given actor can be seen
	// bool LookAtActor(AActor* TargetActor);

	// Can we the given actor
	// added in dodgeball function lib
	//bool CanSeeActor(const AActor* TargetActor) const;

	// Whether the enemy can see the player this frame
	bool CanSeePlayer = false;

	// Whether the enemy could see the player last frame
	bool PreviousCanSeePlayer = false;

	FTimerHandle ThrowTimerHandle;

	// Amount of time to wait between throwing dodgeballs
	float ThrowingInterval = 2.0f;
	// Initial delay before the timer starts looping
	float ThrowingDelay = 0.5f;

	void ThrowDodgeball();
};
