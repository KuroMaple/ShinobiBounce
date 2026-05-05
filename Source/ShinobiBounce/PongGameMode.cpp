// Fill out your copyright notice in the Description page of Project Settings.


#include "PongGameMode.h"

#include "Paddle.h"

APongGameMode::APongGameMode()
{
	DefaultPawnClass = APaddle::StaticClass();
	PlayerControllerClass = APlayerController::StaticClass();
	UE_LOG(LogTemp, Warning, TEXT("PongGameMode constructed"));
}
