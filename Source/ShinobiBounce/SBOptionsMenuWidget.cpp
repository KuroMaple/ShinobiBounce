// Fill out your copyright notice in the Description page of Project Settings.


#include "SBOptionsMenuWidget.h"

#include "SBGameInstance.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void USBOptionsMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	GI = Cast<USBGameInstance>(GetGameInstance());
	if (!GI) return;
	
	OriginalTrackIndex = GI->GetCurrentTrackIndex();
	PreviewTrackIndex = OriginalTrackIndex;
	
	NextTrackButton->OnClicked.AddDynamic(this, &USBOptionsMenuWidget::OnNextTrackClicked);
	PrevTrackButton->OnClicked.AddDynamic(this, &USBOptionsMenuWidget::OnPrevTrackClicked);
	ApplyButton->OnClicked.AddDynamic(this, &USBOptionsMenuWidget::OnApplyClicked);
	BackButton->OnClicked.AddDynamic(this, &USBOptionsMenuWidget::OnBackClicked);
	
	RefreshTrackLabel();
}

void USBOptionsMenuWidget::OnNextTrackClicked()
{
	PreviewTrackIndex = (PreviewTrackIndex + 1) % GI->GetTrackCount();
	GI->PlayTrack(PreviewTrackIndex);
	RefreshTrackLabel();
}

void USBOptionsMenuWidget::OnPrevTrackClicked()
{
	PreviewTrackIndex = (PreviewTrackIndex - 1 + GI->GetTrackCount()) % GI->GetTrackCount();
	GI->PlayTrack(PreviewTrackIndex);
	RefreshTrackLabel();
}

void USBOptionsMenuWidget::OnApplyClicked()
{
	RemoveFromParent();
}

void USBOptionsMenuWidget::OnBackClicked()
{
	if (OriginalTrackIndex != PreviewTrackIndex)
	{
		GI->PlayTrack(OriginalTrackIndex);	
	}
	RemoveFromParent();
}

void USBOptionsMenuWidget::RefreshTrackLabel()
{
	TrackNameText->SetText(GI->GetTrackDisplayName(PreviewTrackIndex));
}
