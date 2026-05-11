// Fill out your copyright notice in the Description page of Project Settings.


#include "PongGameMode.h"

#include "Paddle.h"
#include "ShinobiBounce/SBPlayerController.h"

APongGameMode::APongGameMode()
{
	DefaultPawnClass = APaddle::StaticClass();
	PlayerControllerClass = ASBPlayerController::StaticClass();
}
