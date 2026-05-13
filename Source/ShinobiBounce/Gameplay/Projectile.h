// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UBoxComponent;
class UProjectileMovementComponent;
class UStaticMeshComponent;
class USoundBase;

UCLASS()
class SHINOBIBOUNCE_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> CollisionBox;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> ProjectileMesh;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category=Movement)
	float InitialSpeed = 1000.f;
	
	UPROPERTY(EditDefaultsOnly, Category=Movement)
	FVector2D Direction = FVector2D(-1.f, 0.f);
	
	UFUNCTION()
	void OnBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity);
	
private:
	UPROPERTY(EditDefaultsOnly, Category=Audio)
	TObjectPtr<USoundBase> PaddleHitSfx;
	
	UPROPERTY(EditDefaultsOnly, Category=Audio)
	TObjectPtr<USoundBase> WallHitSfx;
};
