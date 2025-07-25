// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DodgeballProjectile.generated.h"

UCLASS()
class DODGEBALL_API ADodgeballProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADodgeballProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// The damage done to the player upon contact
	UPROPERTY(EditDefaultsOnly, Category = Damage)
	float Damage = 34.0f;

	// The sound the dodgeball will make when it bounces off of a surface
	UPROPERTY(EditAnywhere, Category = Sound)
	class USoundBase* BounceSound;

	// The sound attenuation of the bounce sound
	UPROPERTY(EditAnywhere, Category = Sound)
	class USoundAttenuation* BounceSoundAttenuation;

	UPROPERTY(EditAnywhere, Category = Sound)
	class USoundBase* DamageSound;

	// The particle system the dodgeball will spawn when it hits the player
	UPROPERTY(EditDefaultsOnly, Category = Particles)
	class UParticleSystem* HitParticles;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, 
				UPrimitiveComponent* OtherComp, FVector NormalImpulse, 
				const FHitResult& Hit);

	// Getter for projectile movement
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovementComponent() const {
		return ProjectileMovement;
	}

private:
	// Add sphere components for dodgeball
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Dodgeball, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Dodgeball, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;
};
