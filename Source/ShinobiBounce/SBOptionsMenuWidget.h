// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SBOptionsMenuWidget.generated.h"

class USBGameInstance;
class UButton;
class UTextBlock;
/**
 * 
 */
UCLASS()
class SHINOBIBOUNCE_API USBOptionsMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY()
	TObjectPtr<USBGameInstance> GI;
	
	// Cached index
	int32 OriginalTrackIndex = 0;
	
	// Current Preview index
	int32 PreviewTrackIndex = 0;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> NextTrackButton;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> PrevTrackButton;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> ApplyButton;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> BackButton;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> TrackNameText;
	
	virtual void NativeConstruct() override;
	
	UFUNCTION() void OnNextTrackClicked();
	UFUNCTION() void OnPrevTrackClicked();
	UFUNCTION() void OnApplyClicked();
	UFUNCTION() void OnBackClicked();
	
	void RefreshTrackLabel();
};
