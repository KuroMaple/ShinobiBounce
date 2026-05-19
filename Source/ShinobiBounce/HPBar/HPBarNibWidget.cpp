// Fill out your copyright notice in the Description page of Project Settings.


#include "HPBarNibWidget.h"
#include "Components/Image.h"

void UHPBarNibWidget::SetActive(bool bIsActive)
{
	if (!NibImage) return;
	
	FSlateBrush NewBrush = NibImage->GetBrush();
	
	if (bIsActive)
	{
		if (ActiveMaterial)
		{
			NibImage->SetBrushFromMaterial(ActiveMaterial);
			
			// Ensuring tint of brush remainds white
			
			NewBrush.TintColor = FSlateColor(FLinearColor::White);
			
			NibImage->SetBrush(NewBrush);
		}
	}
	else
	{
		NewBrush.SetResourceObject(nullptr);
		
		NewBrush.TintColor = FSlateColor(FLinearColor(FColor::FromHex(TEXT("636363"))));
		NibImage->SetBrush(NewBrush);
		
	}
}
