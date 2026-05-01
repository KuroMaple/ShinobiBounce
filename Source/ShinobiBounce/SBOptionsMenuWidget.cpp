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
	
	OriginalIdleIndex   = GI->GetCurrentTrackIndex(EMusicType::Idle);
	OriginalFightIndex  = GI->GetCurrentTrackIndex(EMusicType::Fight);
	OriginalEndingIndex = GI->GetCurrentTrackIndex(EMusicType::Ending);
	
	
	NextIdleTrackButton->OnClicked.AddDynamic(this, &USBOptionsMenuWidget::OnNextIdleTrackClicked);
	PrevIdleTrackButton->OnClicked.AddDynamic(this, &USBOptionsMenuWidget::OnPrevIdleTrackClicked);
	NextFightTrackButton->OnClicked.AddDynamic(this, &USBOptionsMenuWidget::OnNextFightTrackClicked);
	PrevFightTrackButton->OnClicked.AddDynamic(this, &USBOptionsMenuWidget::OnPrevFightTrackClicked);
	NextEndingTrackButton->OnClicked.AddDynamic(this, &USBOptionsMenuWidget::OnNextEndingTrackClicked);
	PrevEndingTrackButton->OnClicked.AddDynamic(this, &USBOptionsMenuWidget::OnPrevEndingTrackClicked);
	
	ApplyButton->OnClicked.AddDynamic(this, &USBOptionsMenuWidget::OnApplyClicked);
	BackButton->OnClicked.AddDynamic(this, &USBOptionsMenuWidget::OnBackClicked);
	
	RefreshLabel(EMusicType::Idle);
	RefreshLabel(EMusicType::Fight);
	RefreshLabel(EMusicType::Ending);
}

void USBOptionsMenuWidget::OnNextIdleTrackClicked()
{
	Cycle(EMusicType::Idle, +1);
}

void USBOptionsMenuWidget::OnPrevIdleTrackClicked()
{
	Cycle(EMusicType::Idle, -1);
}

void USBOptionsMenuWidget::OnNextFightTrackClicked()
{
	Cycle(EMusicType::Fight, +1);
}

void USBOptionsMenuWidget::OnPrevFightTrackClicked()
{
	Cycle(EMusicType::Fight, -1);
}

void USBOptionsMenuWidget::OnNextEndingTrackClicked()
{
	Cycle(EMusicType::Ending, +1);
}

void USBOptionsMenuWidget::OnPrevEndingTrackClicked()
{
	Cycle(EMusicType::Ending, -1);
}

void USBOptionsMenuWidget::OnApplyClicked()
{
	GI->PlayTrack(EMusicType::Idle, GI->GetCurrentTrackIndex(EMusicType::Idle));
	RemoveFromParent();
}

void USBOptionsMenuWidget::OnBackClicked()
{
	GI->SetTrackIndex(EMusicType::Idle,   OriginalIdleIndex);
	GI->SetTrackIndex(EMusicType::Fight,  OriginalFightIndex);
	GI->SetTrackIndex(EMusicType::Ending, OriginalEndingIndex);

	GI->PlayTrack(EMusicType::Idle, OriginalIdleIndex);

	RemoveFromParent();
}

void USBOptionsMenuWidget::Cycle(EMusicType Type, int32 Direction)
{
	const int32 Count = GI->GetTrackCount(Type);
	if (Count == 0) return;

	const int32 Current = GI->GetCurrentTrackIndex(Type);
	const int32 NewIndex = (Current + Direction + Count) % Count;
	GI->PlayTrack(Type, NewIndex);
	RefreshLabel(Type);
}

void USBOptionsMenuWidget::RefreshLabel(EMusicType Type)
{
	if (!GI) return;

	const FText Name = GI->GetTrackDisplayName(Type, GI->GetCurrentTrackIndex(Type));

	switch (Type)
	{
		case EMusicType::Idle:   if (IdleTrackNameText)   IdleTrackNameText->SetText(Name);   break;
		case EMusicType::Fight:  if (FightTrackNameText)  FightTrackNameText->SetText(Name);  break;
		case EMusicType::Ending: if (EndingTrackNameText) EndingTrackNameText->SetText(Name); break;
	}
}

