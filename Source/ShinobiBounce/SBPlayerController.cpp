// Fill out your copyright notice in the Description page of Project Settings.


#include "SBPlayerController.h"

#include "Kismet/GameplayStatics.h"

void ASBPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(this, APongCamera::StaticClass(), FoundActors);
	
	UE_LOG(LogTemp, Display, TEXT("SBPlayercontroller begin play, found actor count %d"), FoundActors.Num());
	if (FoundActors.Num() > 0)
	{
		PongCameraActor = Cast<APongCamera>(FoundActors[0]);
		SetViewTarget(PongCameraActor);
	}
}
