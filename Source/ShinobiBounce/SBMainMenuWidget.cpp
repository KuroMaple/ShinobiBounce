// Fill out your copyright notice in the Description page of Project Settings.


#include "SBMainMenuWidget.h"

#include "SBGameInstance.h"
#include "SBOptionsMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void USBMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	PlayButton->OnClicked.AddDynamic(this, &USBMainMenuWidget::OnPlayClicked);
	OptionsButton->OnClicked.AddDynamic(this, &USBMainMenuWidget::OnOptionsClicked);
	ExitButton->OnClicked.AddDynamic(this, &USBMainMenuWidget::OnExitClicked);
	
	
	if (APlayerController* PC = GetOwningPlayer())
	{
		PC->bShowMouseCursor = true;
		FInputModeUIOnly InputMode;
		PC->SetInputMode(InputMode);
	}
	
	if (USBGameInstance* GI = Cast<USBGameInstance>(GetGameInstance()))
	{
		GI->PlayMenuMusic();
	}
}

void USBMainMenuWidget::OnPlayClicked()
{
	
	// Prevent Double triggers
	PlayButton->SetIsEnabled(false);
	OptionsButton->SetIsEnabled(false);
	ExitButton->SetIsEnabled(false);
	
	if (PlayPressedAnim)
	{
		FWidgetAnimationDynamicEvent FinishEvent;
		FinishEvent.BindDynamic(this, &USBMainMenuWidget::OnPlayAnimationFinished);
		BindToAnimationFinished(PlayPressedAnim, FinishEvent);
		
		PlayAnimation(PlayPressedAnim);
	}
	else
	{
		OnPlayAnimationFinished();
	}
}

void USBMainMenuWidget::OnOptionsClicked()
{
	if (!OptionsMenuClass) return;
	USBOptionsMenuWidget* OptionsWidget = CreateWidget<USBOptionsMenuWidget>(GetOwningPlayer(), OptionsMenuClass);
	if (OptionsWidget) OptionsWidget->AddToViewport();
}

void USBMainMenuWidget::OnExitClicked()
{
	UKismetSystemLibrary::QuitGame(
		this,
		GetOwningPlayer(),
		EQuitPreference::Quit,
		true
		);
}

void USBMainMenuWidget::OnPlayAnimationFinished()
{
	UGameplayStatics::OpenLevel(this, PlayLevelName);
}
