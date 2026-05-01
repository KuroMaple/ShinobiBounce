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
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

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

	struct FHoverState
	{
		float Current = 0.f;
		float Target  = 0.f;
	};

	struct FHoverButton
	{
		TObjectPtr<UButton> Button;
		FHoverState HoverState;
		FHoverState PressState;
		FVector2D BaseScale = FVector2D(1.f, 1.f);
	};

	TArray<FHoverButton> HoverButtons;

	UPROPERTY(EditDefaultsOnly, Category=Animation)
	float HoverLerpSpeed = 8.f;

	UPROPERTY(EditDefaultsOnly, Category=Animation)
	float HoverScale = 1.1f;

	UPROPERTY(EditDefaultsOnly, Category=Animation)
	float PressLerpSpeed = 20.f;

	UPROPERTY(EditDefaultsOnly, Category=Animation)
	float PressScale = 0.95f;

	UPROPERTY(EditDefaultsOnly, Category=Animation)
	FLinearColor RestTint = FLinearColor::White;

	UPROPERTY(EditDefaultsOnly, Category=Animation)
	FLinearColor HoverTint = FLinearColor(1.2f, 1.1f, 0.7f, 1.f);

	void RegisterHoverButton(UButton* Button);
	void SetHoverTarget(UButton* Button, float Target);
	void SetPressTarget(UButton* Button, float Target);

	UFUNCTION() void OnApplyHovered();
	UFUNCTION() void OnApplyUnhovered();
	UFUNCTION() void OnApplyPressed();
	UFUNCTION() void OnApplyReleased();

	UFUNCTION() void OnBackHovered();
	UFUNCTION() void OnBackUnhovered();
	UFUNCTION() void OnBackPressed();
	UFUNCTION() void OnBackReleased();

	UFUNCTION() void OnNextIdleHovered();
	UFUNCTION() void OnNextIdleUnhovered();
	UFUNCTION() void OnNextIdlePressed();
	UFUNCTION() void OnNextIdleReleased();

	UFUNCTION() void OnPrevIdleHovered();
	UFUNCTION() void OnPrevIdleUnhovered();
	UFUNCTION() void OnPrevIdlePressed();
	UFUNCTION() void OnPrevIdleReleased();

	UFUNCTION() void OnNextFightHovered();
	UFUNCTION() void OnNextFightUnhovered();
	UFUNCTION() void OnNextFightPressed();
	UFUNCTION() void OnNextFightReleased();

	UFUNCTION() void OnPrevFightHovered();
	UFUNCTION() void OnPrevFightUnhovered();
	UFUNCTION() void OnPrevFightPressed();
	UFUNCTION() void OnPrevFightReleased();

	UFUNCTION() void OnNextEndingHovered();
	UFUNCTION() void OnNextEndingUnhovered();
	UFUNCTION() void OnNextEndingPressed();
	UFUNCTION() void OnNextEndingReleased();

	UFUNCTION() void OnPrevEndingHovered();
	UFUNCTION() void OnPrevEndingUnhovered();
	UFUNCTION() void OnPrevEndingPressed();
	UFUNCTION() void OnPrevEndingReleased();
};
