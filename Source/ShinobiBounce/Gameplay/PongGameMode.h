// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PongGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SHINOBIBOUNCE_API APongGameMode : public AGameModeBase
{
	GENERATED_BODY()
	APongGameMode();
	
	UPROPERTY(EditDefaultsOnly, Category=Difficulty)
	float SpeedIncreasePerHit = 1.05f;
	
	UPROPERTY(EditDefaultsOnly, Category=Difficulty)
	float MaxSpeed = 3000.f;
	
	int32 RallyHitCount = 0;
	
	virtual void BeginPlay() override;
public:
	void OnPaddleHit(class AProjectile* Projectile);
	void ResetRally();
	
	
};
