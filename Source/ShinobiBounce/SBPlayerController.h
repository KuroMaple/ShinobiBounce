// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/PongCamera.h"
#include "GameFramework/PlayerController.h"
#include "SBPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SHINOBIBOUNCE_API ASBPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY()
	TObjectPtr<APongCamera> PongCameraActor;
	
};
