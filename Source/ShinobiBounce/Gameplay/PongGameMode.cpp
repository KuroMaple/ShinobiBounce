// Fill out your copyright notice in the Description page of Project Settings.


#include "PongGameMode.h"

#include "Paddle.h"
#include "ShinobiBounce/SBGameInstance.h"
#include "ShinobiBounce/SBPlayerController.h"

APongGameMode::APongGameMode()
{
	DefaultPawnClass = APaddle::StaticClass();
	PlayerControllerClass = ASBPlayerController::StaticClass();
}

void APongGameMode::BeginPlay()
{
	Super::BeginPlay();
	if (USBGameInstance* GI = Cast<USBGameInstance>(GetGameInstance()))
	{
		const int32 Index = GI->GetCurrentTrackIndex(EMusicType::Fight);
		GI->PlayTrack(EMusicType::Fight, Index);
	}
}
