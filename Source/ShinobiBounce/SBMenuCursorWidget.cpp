// Fill out your copyright notice in the Description page of Project Settings.


#include "SBMenuCursorWidget.h"

#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"

void USBMenuCursorWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	// Debugging
	UE_LOG(LogTemp, Warning, TEXT("Cursor tick. PC=%s Image=%s"),
		GetOwningPlayer() ? TEXT("ok") : TEXT("NULL"),
		CursorImage ? TEXT("ok") : TEXT("NULL"));
	
	const bool bDown = FSlateApplication::Get()
		.GetPressedMouseButtons()
		.Contains(EKeys::LeftMouseButton);
	
	ClickTarget = bDown ? 1.f : 0.f;
	ClickCurrent = FMath::FInterpTo(ClickCurrent, ClickTarget, InDeltaTime, ClickLerpSpeed);
	
	const float Scale = FMath::Lerp(1.f, ClickScale, ClickCurrent);
	if (CursorImage) CursorImage->SetRenderScale(FVector2D(Scale, Scale));
}
