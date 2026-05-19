// Fill out your copyright notice in the Description page of Project Settings.


#include "HPBarWidget.h"
#include "HPBarNibWidget.h"
#include "Components/Border.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/SizeBox.h"
#include "Materials/MaterialInstanceDynamic.h"

void UHPBarWidget::SetInitialHP(int32 HPAmount)
{
	// TODO: when paramter is fixed, uncomment below
	// if (!Actor.isValid)
	// {
	// 	this->SetVisibility(ESlateVisibility::Hidden);
	// }
	// else
	// {
	// 	this->SetVisibility(ESlateVisibility::Visible);
	// }
	
	//int32 HPAmount = Actor->GetHP();
	// int32 HPPerNib = Actor->GetHPPerNib();
	
	UpdateMainBarWidth(HPAmount);
	
	const int32 TargetNibCount = GetNibCount(HPAmount);
	EnsureNibCount(TargetNibCount);
	
	RefreshNibActiveStates(HPAmount);
	
	// Debugging
	ensure(HPBarSizeBox);
	ensure(NibContainer);
	ensure(NibWidgetClass);
	
	UE_LOG(LogTemp, Warning, TEXT("SetInitialHP: MaxHP set to %d"), HPAmount);
}

void UHPBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (HPBorderMaterial && HPMainBorder)
	{
		HPBorderMID = UMaterialInstanceDynamic::Create(HPBorderMaterial, this);
		if (HPBorderMID)
		{
			HPMainBorder->SetBrushFromMaterial(HPBorderMID);
			HPBorderMID->SetScalarParameterValue(TEXT("Health"), 1.0);
			UE_LOG(LogTemp, Warning, TEXT("MID created and applied to border"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("MID creation FAILED"));
		}
	}
}

void UHPBarWidget::UpdateHP(int32 HPAmount)
{
	
	if (HPPerNib <= 0) return;
	
	HPAmount = FMath::Clamp(HPAmount, 0, MaxHP);
	
	// Update entity HP here
	// e.g CurrentHP = HPAmount
	
	RefreshNibActiveStates(HPAmount);
	
	const int32 ActiveExtraNibs = FMath::Max(0, FMath::CeilToInt(static_cast<float>(HPAmount) / HPPerNib) - 1);
	const int32 HPInCurrentSegment = HPAmount - (ActiveExtraNibs * HPPerNib);
	const double SegmentRatio = static_cast<float>(HPInCurrentSegment) / HPPerNib;
	
	if (HPBorderMID)
	{
		HPBorderMID->SetScalarParameterValue(TEXT("Health"), SegmentRatio);
		UE_LOG(LogTemp, Verbose, TEXT("Set Health scalar = %.3f"), SegmentRatio);	
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("HPBorderMID is NULL during UpdateHP"));
	}
	
	UE_LOG(LogTemp, Warning, TEXT("UpdateHP called: HPAmount=%d, HPPerNib=%d, MaxHP=%d"),
	   HPAmount, HPPerNib, MaxHP);
}

void UHPBarWidget::UpdateMainBarWidth(int32 HPAmount)
{
	if (!HPBarSizeBox || HPPerNib <= 0) return;
	
	if (HPAmount < HPPerNib)
	{
		const float WidthRatio = static_cast<float>(HPAmount) / HPPerNib;
		HPBarSizeBox->SetWidthOverride(20.f);
		
		HPBarSizeBox->SetWidthOverride(MaxHPBarWidth * WidthRatio);
	}
	else
	{
		HPBarSizeBox->SetWidthOverride(MaxHPBarWidth);
	}
}

int32 UHPBarWidget::GetNibCount(int32 HPAmount) const
{
	if (HPAmount <= HPPerNib || HPPerNib <= 0) return 0;
	
	const int32 TotalSegments = FMath::CeilToInt(static_cast<float>(HPAmount) / HPPerNib);
	return FMath::Max(0, TotalSegments - 1);
}

void UHPBarWidget::EnsureNibCount(int32 TargetCount)
{
	if (!NibContainer || !NibWidgetClass) return;
	
	const int32 CurrentCount = SpawnedNibs.Num();
	
	if (CurrentCount < TargetCount)
	{
		for (int32 i = CurrentCount; i < TargetCount; ++i)
		{
			UHPBarNibWidget* NewNib = CreateWidget<UHPBarNibWidget>(this, NibWidgetClass);
		
			if (!NewNib) continue;
			
			UPanelSlot* CurrentSlot = NibContainer->AddChild(NewNib);
			if (UHorizontalBoxSlot* HBoxSlot = Cast<UHorizontalBoxSlot>(CurrentSlot))
			{
				HBoxSlot->SetPadding(FMargin(1.f, 1.f, 1.f, 0.f));
				HBoxSlot->SetHorizontalAlignment(HAlign_Center);
				HBoxSlot->SetVerticalAlignment(VAlign_Center);
			}
			
			SpawnedNibs.Add(NewNib);
		}
		
	}
	else if (CurrentCount > TargetCount)
	{
		// Remove excess from the end
		for (int32 i = CurrentCount - 1; i >= TargetCount; i--)
		{
			if (SpawnedNibs[i])
			{
				SpawnedNibs[i]->RemoveFromParent();
			}
			SpawnedNibs.RemoveAt(i);
		}
	}
}

void UHPBarWidget::RefreshNibActiveStates(int32 HPAmount)
{
	for (int32 i = 0; i < SpawnedNibs.Num(); ++i)
	{
		if (!SpawnedNibs[i]) continue;
		const int32 HPThreshold = (i + 1) * HPPerNib;
		const bool bIsActive = HPAmount >= HPThreshold;
		
		SpawnedNibs[i]->SetActive(bIsActive);
	}
}
