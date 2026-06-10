// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIPaddle.h"
#include "NarutoClonePaddle.generated.h"

/**
 * 
 */
UCLASS()
class SHINOBIBOUNCE_API ANarutoClonePaddle : public AAIPaddle
{
	GENERATED_BODY()
	
	virtual void CreateHPBar() override;
	
};
