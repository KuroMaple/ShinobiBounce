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
	
	
	virtual void NativeConstruct() override;
	
	UFUNCTION() void OnPlayClicked();
	UFUNCTION() void OnOptionsClicked();
	UFUNCTION() void OnExitClicked();
	
	UFUNCTION() void OnPlayAnimationFinished();
};
