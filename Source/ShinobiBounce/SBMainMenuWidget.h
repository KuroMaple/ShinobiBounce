// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SBMainMenuWidget.generated.h"

class USBOptionsMenuWidget;
class UButton;
/**
 * 
 */
UCLASS()
class SHINOBIBOUNCE_API USBMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, Category=UI)
	TSubclassOf<USBOptionsMenuWidget> OptionsMenuClass;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> PlayButton;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> OptionsButton;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> ExitButton;
	
	UPROPERTY(Transient, meta=(BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> PlayPressedAnim;
	
	UPROPERTY(EditDefaultsOnly, Category=Levels)
	FName PlayLevelName = TEXT("BasicOpenWorld");

	struct FHoverState
	{
		float Current = 0.f;
		float Target = 0.f;
	};
	
	struct FHoverButton
	{
		TObjectPtr<UButton> Button;
		FHoverState State;
		FVector2D BaseScale = FVector2D(1.f, 1.f);
	};

	TArray<FHoverButton> HoverButtons;
	
	
	UPROPERTY(EditDefaultsOnly, Category=Animation)
	float HoverLerpSpeed = 8.f;
	
	UPROPERTY(EditDefaultsOnly, Category=Animation)
	float HoverScale = 1.1f;
	
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	
	UFUNCTION() void OnPlayClicked();
	UFUNCTION() void OnOptionsClicked();
	UFUNCTION() void OnExitClicked();
	
	UFUNCTION() void OnPlayAnimationFinished();
	
	void SetHoverTarget(UButton* Button, float Target);
	void RegisterHoverButton(UButton* Button);
	
	UFUNCTION() void OnPlayHovered();
	UFUNCTION() void OnPlayUnhovered();
	UFUNCTION() void OnOptionsHovered();
	UFUNCTION() void OnOptionsUnhovered();
	UFUNCTION() void OnExitHovered();
	UFUNCTION() void OnExitUnhovered();
};
