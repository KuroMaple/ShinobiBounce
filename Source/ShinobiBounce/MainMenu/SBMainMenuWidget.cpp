// Fill out your copyright notice in the Description page of Project Settings.


#include "SBMainMenuWidget.h"

#include "ShinobiBounce/SBGameInstance.h"
#include "SBOptionsMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void USBMainMenuWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	for (FHoverButton& Entry : HoverButtons)
	{
		Entry.HoverState.Current = FMath::FInterpTo(
			Entry.HoverState.Current, Entry.HoverState.Target, InDeltaTime, HoverLerpSpeed);
		
		Entry.PressState.Current = FMath::FInterpTo(
			Entry.PressState.Current, Entry.PressState.Target, InDeltaTime, PressLerpSpeed);
		
		const float HoverMult = FMath::Lerp(1.f, HoverScale, Entry.HoverState.Current);
		const float PressMult = FMath::Lerp(1.f, PressScale, Entry.PressState.Current);
		Entry.Button->SetRenderScale(Entry.BaseScale * HoverMult * PressMult);
	}
}

void USBMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	PlayButton->OnClicked.AddDynamic(this, &USBMainMenuWidget::OnPlayClicked);
	OptionsButton->OnClicked.AddDynamic(this, &USBMainMenuWidget::OnOptionsClicked);
	ExitButton->OnClicked.AddDynamic(this, &USBMainMenuWidget::OnExitClicked);
	
	RegisterHoverButton(PlayButton);
	RegisterHoverButton(OptionsButton);
	RegisterHoverButton(ExitButton);

	PlayButton->OnHovered.AddDynamic(this, &USBMainMenuWidget::OnPlayHovered);
	PlayButton->OnUnhovered.AddDynamic(this, &USBMainMenuWidget::OnPlayUnhovered);
	OptionsButton->OnHovered.AddDynamic(this, &USBMainMenuWidget::OnOptionsHovered);
	OptionsButton->OnUnhovered.AddDynamic(this, &USBMainMenuWidget::OnOptionsUnhovered);
	ExitButton->OnHovered.AddDynamic(this, &USBMainMenuWidget::OnExitHovered);
	ExitButton->OnUnhovered.AddDynamic(this, &USBMainMenuWidget::OnExitUnhovered);
	
	PlayButton->OnPressed.AddDynamic(this, &USBMainMenuWidget::OnPlayPressed);
	PlayButton->OnReleased.AddDynamic(this, &USBMainMenuWidget::OnPlayReleased);
	OptionsButton->OnPressed.AddDynamic(this, &USBMainMenuWidget::OnOptionsPressed);
	OptionsButton->OnReleased.AddDynamic(this, &USBMainMenuWidget::OnOptionsReleased);
	ExitButton->OnPressed.AddDynamic(this, &USBMainMenuWidget::OnExitPressed);
	ExitButton->OnReleased.AddDynamic(this, &USBMainMenuWidget::OnExitReleased);
	
	if (APlayerController* PC = GetOwningPlayer())
	{
		PC->bShowMouseCursor = true;
		FInputModeUIOnly InputMode;
		PC->SetInputMode(InputMode);
	}
	
	if (USBGameInstance* GI = Cast<USBGameInstance>(GetGameInstance()))
	{
		GI->PlayIdleMusic();
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

void USBMainMenuWidget::SetHoverTarget(UButton* Button, float Target)
{
	for (FHoverButton & Entry : HoverButtons)
	{
		if (Entry.Button == Button) { Entry.HoverState.Target = Target; return; }
	}
}

void USBMainMenuWidget::SetPressTarget(UButton* Button, float Target)
{
	for (FHoverButton & Entry : HoverButtons)
	{
		if (Entry.Button == Button) { Entry.PressState.Target = Target; return; }
	}
}

void USBMainMenuWidget::RegisterHoverButton(UButton* Button)
{
	if (!Button) return;
	FHoverButton Entry;
	Entry.Button = Button;
	Entry.BaseScale = Button->GetRenderTransform().Scale; // Capture Blueprint scale
	HoverButtons.Add(Entry);
}

void USBMainMenuWidget::OnPlayHovered()      { SetHoverTarget(PlayButton, 1.f); }
void USBMainMenuWidget::OnPlayUnhovered()    { SetHoverTarget(PlayButton, 0.f); SetPressTarget(PlayButton, 0.f); }
void USBMainMenuWidget::OnOptionsHovered()   { SetHoverTarget(OptionsButton, 1.f); }
void USBMainMenuWidget::OnOptionsUnhovered() { SetHoverTarget(OptionsButton, 0.f); SetPressTarget(OptionsButton, 0.f); }   
void USBMainMenuWidget::OnExitHovered()      { SetHoverTarget(ExitButton, 1.f); }
void USBMainMenuWidget::OnExitUnhovered()    { SetHoverTarget(ExitButton, 0.f); SetPressTarget(ExitButton, 0.f); }       

void USBMainMenuWidget::OnPlayPressed()      { SetPressTarget(PlayButton, 1.f); }
void USBMainMenuWidget::OnPlayReleased()     { SetPressTarget(PlayButton, 0.f); }
void USBMainMenuWidget::OnOptionsPressed()   { SetPressTarget(OptionsButton, 1.f); }
void USBMainMenuWidget::OnOptionsReleased()  { SetPressTarget(OptionsButton, 0.f); }
void USBMainMenuWidget::OnExitPressed()      { SetPressTarget(ExitButton, 1.f); }
void USBMainMenuWidget::OnExitReleased()     { SetPressTarget(ExitButton, 0.f); }
