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

	RegisterHoverButton(ApplyButton);
	RegisterHoverButton(BackButton);
	RegisterHoverButton(NextIdleTrackButton);
	RegisterHoverButton(PrevIdleTrackButton);
	RegisterHoverButton(NextFightTrackButton);
	RegisterHoverButton(PrevFightTrackButton);
	RegisterHoverButton(NextEndingTrackButton);
	RegisterHoverButton(PrevEndingTrackButton);

	ApplyButton->OnHovered.AddDynamic(this, &USBOptionsMenuWidget::OnApplyHovered);
	ApplyButton->OnUnhovered.AddDynamic(this, &USBOptionsMenuWidget::OnApplyUnhovered);
	ApplyButton->OnPressed.AddDynamic(this, &USBOptionsMenuWidget::OnApplyPressed);
	ApplyButton->OnReleased.AddDynamic(this, &USBOptionsMenuWidget::OnApplyReleased);

	BackButton->OnHovered.AddDynamic(this, &USBOptionsMenuWidget::OnBackHovered);
	BackButton->OnUnhovered.AddDynamic(this, &USBOptionsMenuWidget::OnBackUnhovered);
	BackButton->OnPressed.AddDynamic(this, &USBOptionsMenuWidget::OnBackPressed);
	BackButton->OnReleased.AddDynamic(this, &USBOptionsMenuWidget::OnBackReleased);

	NextIdleTrackButton->OnHovered.AddDynamic(this, &USBOptionsMenuWidget::OnNextIdleHovered);
	NextIdleTrackButton->OnUnhovered.AddDynamic(this, &USBOptionsMenuWidget::OnNextIdleUnhovered);
	NextIdleTrackButton->OnPressed.AddDynamic(this, &USBOptionsMenuWidget::OnNextIdlePressed);
	NextIdleTrackButton->OnReleased.AddDynamic(this, &USBOptionsMenuWidget::OnNextIdleReleased);

	PrevIdleTrackButton->OnHovered.AddDynamic(this, &USBOptionsMenuWidget::OnPrevIdleHovered);
	PrevIdleTrackButton->OnUnhovered.AddDynamic(this, &USBOptionsMenuWidget::OnPrevIdleUnhovered);
	PrevIdleTrackButton->OnPressed.AddDynamic(this, &USBOptionsMenuWidget::OnPrevIdlePressed);
	PrevIdleTrackButton->OnReleased.AddDynamic(this, &USBOptionsMenuWidget::OnPrevIdleReleased);

	NextFightTrackButton->OnHovered.AddDynamic(this, &USBOptionsMenuWidget::OnNextFightHovered);
	NextFightTrackButton->OnUnhovered.AddDynamic(this, &USBOptionsMenuWidget::OnNextFightUnhovered);
	NextFightTrackButton->OnPressed.AddDynamic(this, &USBOptionsMenuWidget::OnNextFightPressed);
	NextFightTrackButton->OnReleased.AddDynamic(this, &USBOptionsMenuWidget::OnNextFightReleased);

	PrevFightTrackButton->OnHovered.AddDynamic(this, &USBOptionsMenuWidget::OnPrevFightHovered);
	PrevFightTrackButton->OnUnhovered.AddDynamic(this, &USBOptionsMenuWidget::OnPrevFightUnhovered);
	PrevFightTrackButton->OnPressed.AddDynamic(this, &USBOptionsMenuWidget::OnPrevFightPressed);
	PrevFightTrackButton->OnReleased.AddDynamic(this, &USBOptionsMenuWidget::OnPrevFightReleased);

	NextEndingTrackButton->OnHovered.AddDynamic(this, &USBOptionsMenuWidget::OnNextEndingHovered);
	NextEndingTrackButton->OnUnhovered.AddDynamic(this, &USBOptionsMenuWidget::OnNextEndingUnhovered);
	NextEndingTrackButton->OnPressed.AddDynamic(this, &USBOptionsMenuWidget::OnNextEndingPressed);
	NextEndingTrackButton->OnReleased.AddDynamic(this, &USBOptionsMenuWidget::OnNextEndingReleased);

	PrevEndingTrackButton->OnHovered.AddDynamic(this, &USBOptionsMenuWidget::OnPrevEndingHovered);
	PrevEndingTrackButton->OnUnhovered.AddDynamic(this, &USBOptionsMenuWidget::OnPrevEndingUnhovered);
	PrevEndingTrackButton->OnPressed.AddDynamic(this, &USBOptionsMenuWidget::OnPrevEndingPressed);
	PrevEndingTrackButton->OnReleased.AddDynamic(this, &USBOptionsMenuWidget::OnPrevEndingReleased);

	RefreshLabel(EMusicType::Idle);
	RefreshLabel(EMusicType::Fight);
	RefreshLabel(EMusicType::Ending);
}

void USBOptionsMenuWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
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

		const FLinearColor Tint = FMath::Lerp(RestTint, HoverTint, Entry.HoverState.Current);
		Entry.Button->SetColorAndOpacity(Tint);
	}
}

void USBOptionsMenuWidget::RegisterHoverButton(UButton* Button)
{
	if (!Button) return;
	FHoverButton Entry;
	Entry.Button = Button;
	Entry.BaseScale = Button->GetRenderTransform().Scale;
	HoverButtons.Add(Entry);
}

void USBOptionsMenuWidget::SetHoverTarget(UButton* Button, float Target)
{
	for (FHoverButton& Entry : HoverButtons)
	{
		if (Entry.Button == Button) { Entry.HoverState.Target = Target; return; }
	}
}

void USBOptionsMenuWidget::SetPressTarget(UButton* Button, float Target)
{
	for (FHoverButton& Entry : HoverButtons)
	{
		if (Entry.Button == Button) { Entry.PressState.Target = Target; return; }
	}
}

void USBOptionsMenuWidget::OnApplyHovered()    { SetHoverTarget(ApplyButton, 1.f); }
void USBOptionsMenuWidget::OnApplyUnhovered()  { SetHoverTarget(ApplyButton, 0.f); SetPressTarget(ApplyButton, 0.f); }
void USBOptionsMenuWidget::OnApplyPressed()    { SetPressTarget(ApplyButton, 1.f); }
void USBOptionsMenuWidget::OnApplyReleased()   { SetPressTarget(ApplyButton, 0.f); }

void USBOptionsMenuWidget::OnBackHovered()     { SetHoverTarget(BackButton, 1.f); }
void USBOptionsMenuWidget::OnBackUnhovered()   { SetHoverTarget(BackButton, 0.f); SetPressTarget(BackButton, 0.f); }
void USBOptionsMenuWidget::OnBackPressed()     { SetPressTarget(BackButton, 1.f); }
void USBOptionsMenuWidget::OnBackReleased()    { SetPressTarget(BackButton, 0.f); }

void USBOptionsMenuWidget::OnNextIdleHovered()    { SetHoverTarget(NextIdleTrackButton, 1.f); }
void USBOptionsMenuWidget::OnNextIdleUnhovered()  { SetHoverTarget(NextIdleTrackButton, 0.f); SetPressTarget(NextIdleTrackButton, 0.f); }
void USBOptionsMenuWidget::OnNextIdlePressed()    { SetPressTarget(NextIdleTrackButton, 1.f); }
void USBOptionsMenuWidget::OnNextIdleReleased()   { SetPressTarget(NextIdleTrackButton, 0.f); }

void USBOptionsMenuWidget::OnPrevIdleHovered()    { SetHoverTarget(PrevIdleTrackButton, 1.f); }
void USBOptionsMenuWidget::OnPrevIdleUnhovered()  { SetHoverTarget(PrevIdleTrackButton, 0.f); SetPressTarget(PrevIdleTrackButton, 0.f); }
void USBOptionsMenuWidget::OnPrevIdlePressed()    { SetPressTarget(PrevIdleTrackButton, 1.f); }
void USBOptionsMenuWidget::OnPrevIdleReleased()   { SetPressTarget(PrevIdleTrackButton, 0.f); }

void USBOptionsMenuWidget::OnNextFightHovered()    { SetHoverTarget(NextFightTrackButton, 1.f); }
void USBOptionsMenuWidget::OnNextFightUnhovered()  { SetHoverTarget(NextFightTrackButton, 0.f); SetPressTarget(NextFightTrackButton, 0.f); }
void USBOptionsMenuWidget::OnNextFightPressed()    { SetPressTarget(NextFightTrackButton, 1.f); }
void USBOptionsMenuWidget::OnNextFightReleased()   { SetPressTarget(NextFightTrackButton, 0.f); }

void USBOptionsMenuWidget::OnPrevFightHovered()    { SetHoverTarget(PrevFightTrackButton, 1.f); }
void USBOptionsMenuWidget::OnPrevFightUnhovered()  { SetHoverTarget(PrevFightTrackButton, 0.f); SetPressTarget(PrevFightTrackButton, 0.f); }
void USBOptionsMenuWidget::OnPrevFightPressed()    { SetPressTarget(PrevFightTrackButton, 1.f); }
void USBOptionsMenuWidget::OnPrevFightReleased()   { SetPressTarget(PrevFightTrackButton, 0.f); }

void USBOptionsMenuWidget::OnNextEndingHovered()    { SetHoverTarget(NextEndingTrackButton, 1.f); }
void USBOptionsMenuWidget::OnNextEndingUnhovered()  { SetHoverTarget(NextEndingTrackButton, 0.f); SetPressTarget(NextEndingTrackButton, 0.f); }
void USBOptionsMenuWidget::OnNextEndingPressed()    { SetPressTarget(NextEndingTrackButton, 1.f); }
void USBOptionsMenuWidget::OnNextEndingReleased()   { SetPressTarget(NextEndingTrackButton, 0.f); }

void USBOptionsMenuWidget::OnPrevEndingHovered()    { SetHoverTarget(PrevEndingTrackButton, 1.f); }
void USBOptionsMenuWidget::OnPrevEndingUnhovered()  { SetHoverTarget(PrevEndingTrackButton, 0.f); SetPressTarget(PrevEndingTrackButton, 0.f); }
void USBOptionsMenuWidget::OnPrevEndingPressed()    { SetPressTarget(PrevEndingTrackButton, 1.f); }
void USBOptionsMenuWidget::OnPrevEndingReleased()   { SetPressTarget(PrevEndingTrackButton, 0.f); }

void USBOptionsMenuWidget::OnNextIdleTrackClicked()  { Cycle(EMusicType::Idle, +1); }
void USBOptionsMenuWidget::OnPrevIdleTrackClicked()  { Cycle(EMusicType::Idle, -1); }
void USBOptionsMenuWidget::OnNextFightTrackClicked() { Cycle(EMusicType::Fight, +1); }
void USBOptionsMenuWidget::OnPrevFightTrackClicked() { Cycle(EMusicType::Fight, -1); }
void USBOptionsMenuWidget::OnNextEndingTrackClicked(){ Cycle(EMusicType::Ending, +1); }
void USBOptionsMenuWidget::OnPrevEndingTrackClicked(){ Cycle(EMusicType::Ending, -1); }

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
