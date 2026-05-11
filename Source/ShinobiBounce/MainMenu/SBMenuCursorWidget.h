// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SBMenuCursorWidget.generated.h"

class UImage;
/**
 * 
 */
UCLASS()
class SHINOBIBOUNCE_API USBMenuCursorWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> CursorImage;
	
	UPROPERTY(EditDefaultsOnly, Category=Audio)
	TObjectPtr<USoundBase> ClickSFX;
	
	UPROPERTY(EditDefaultsOnly, Category=Animation)
	float ClickScale = 0.55f;
	
	UPROPERTY(EditDefaultsOnly, Category=Animation)
	float ClickLerpSpeed = 25.f;
	
	UPROPERTY(EditDefaultsOnly, Category=Animation)
	float ClickRotationDegrees = -16.f;
	
	UPROPERTY(EditDefaultsOnly, Category=Animation)
	float ClickImpulseDecay = 6.f;
	
	bool bWasDownLastTick = false;
	float ClickImpulse = 0.f;
	
	float ClickCurrent = 0.f;
	float ClickTarget = 0.f;
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
