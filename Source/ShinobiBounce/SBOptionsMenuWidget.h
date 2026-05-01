// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SBGameInstance.h"
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
	
	int32 OriginalIdleIndex = 0;
	int32 OriginalFightIndex = 0;
	int32 OriginalEndingIndex = 0;
	
	UPROPERTY(meta=(BindWidget)) TObjectPtr<UButton> NextIdleTrackButton;
	UPROPERTY(meta=(BindWidget)) TObjectPtr<UButton> PrevIdleTrackButton;
	UPROPERTY(meta=(BindWidget)) TObjectPtr<UTextBlock> IdleTrackNameText;

	UPROPERTY(meta=(BindWidget)) TObjectPtr<UButton> NextFightTrackButton;
	UPROPERTY(meta=(BindWidget)) TObjectPtr<UButton> PrevFightTrackButton;
	UPROPERTY(meta=(BindWidget)) TObjectPtr<UTextBlock> FightTrackNameText;

	UPROPERTY(meta=(BindWidget)) TObjectPtr<UButton> NextEndingTrackButton;
	UPROPERTY(meta=(BindWidget)) TObjectPtr<UButton> PrevEndingTrackButton;
	UPROPERTY(meta=(BindWidget)) TObjectPtr<UTextBlock> EndingTrackNameText;

	UPROPERTY(meta=(BindWidget)) TObjectPtr<UButton> ApplyButton;
	UPROPERTY(meta=(BindWidget)) TObjectPtr<UButton> BackButton;
	
	virtual void NativeConstruct() override;
	
	UFUNCTION() void OnNextIdleTrackClicked();
	UFUNCTION() void OnPrevIdleTrackClicked();
	UFUNCTION() void OnNextFightTrackClicked();
	UFUNCTION() void OnPrevFightTrackClicked();
	UFUNCTION() void OnNextEndingTrackClicked();
	UFUNCTION() void OnPrevEndingTrackClicked();

	UFUNCTION() void OnApplyClicked();
	UFUNCTION() void OnBackClicked();
	
	void Cycle(EMusicType Type, int32 Direction);
	void RefreshLabel(EMusicType Type);
};
