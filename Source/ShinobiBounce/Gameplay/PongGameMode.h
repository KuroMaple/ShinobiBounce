// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShinobiBounce/PongTypes.h"
#include "PongGameMode.generated.h"

class AProjectile;
class APaddle;
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
	int32 DamagePerHit = 100;
	UPROPERTY()
	TObjectPtr<APaddle> LeftPaddle;
	
	UPROPERTY()
	TObjectPtr<APaddle> RightPaddle;
	
	UPROPERTY()
	TObjectPtr<AProjectile> ActiveProjectile;
	
	virtual void BeginPlay() override;
public:
	void OnPaddleHit(AProjectile* Projectile);
	void ResetRally();
	void OnPaddleDefeated(APaddle* LosingPaddle);
	void OnGoalHit(EGoalSide HitSide);
	void RespawnProjectile(EGoalSide HitSide);
};
