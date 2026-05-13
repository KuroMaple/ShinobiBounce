// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Paddle.h"
#include "AIPaddle.generated.h"

/**
 * 
 */
UCLASS()
class SHINOBIBOUNCE_API AAIPaddle : public APaddle
{
	GENERATED_BODY()
	AAIPaddle();
protected:
	UPROPERTY()
	TObjectPtr<AProjectile> TrackedProjectile;
	
	UPROPERTY(EditDefaultsOnly, Category=AI)
	float DeadzoneRadius = 10.f;
	
	virtual void BeginPlay() override;
	virtual void UpdateMovement(float DeltaTime) override;
	virtual bool ShouldSetUpPlayerInput() const override { return false; }
	
};
