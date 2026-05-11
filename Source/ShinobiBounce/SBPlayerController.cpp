// Fill out your copyright notice in the Description page of Project Settings.


#include "SBPlayerController.h"

#include "Kismet/GameplayStatics.h"

void ASBPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	FInputModeGameOnly GameInput;
	SetInputMode(GameInput);
	bShowMouseCursor = false;
	
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(this, APongCamera::StaticClass(), FoundActors);
	if (FoundActors.Num() > 0)
	{
		PongCameraActor = Cast<APongCamera>(FoundActors[0]);
		SetViewTarget(PongCameraActor);
	}
	
	SetControlRotation(FRotator(0, 0, 0));

}
