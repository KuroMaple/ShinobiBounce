// Fill out your copyright notice in the Description page of Project Settings.


#include "SBMenuCursorWidget.h"

#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"

void USBMenuCursorWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	const bool bDown = FSlateApplication::Get()
		.GetPressedMouseButtons()
		.Contains(EKeys::LeftMouseButton);
	
	const bool bRisingEdge = bDown && !bWasDownLastTick;
	bWasDownLastTick = bDown;
	
	if (bRisingEdge)
	{
		ClickImpulse = 1.f;
		if (ClickSFX) UGameplayStatics::PlaySound2D(this, ClickSFX);
	}
	
	ClickImpulse = FMath::FInterpTo(ClickImpulse, 0.f, InDeltaTime, ClickImpulseDecay);
	
	ClickTarget = bDown ? 1.f : 0.f;
	ClickCurrent = FMath::FInterpTo(ClickCurrent, ClickTarget, InDeltaTime, ClickLerpSpeed);
	
	const float Scale = FMath::Lerp(1.f, ClickScale, ClickCurrent);
	if (CursorImage)
	{
		CursorImage->SetRenderScale(FVector2D(Scale, Scale));
		CursorImage->SetRenderTransformAngle(ClickImpulse * ClickRotationDegrees);
	}
}
