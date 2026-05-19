// Fill out your copyright notice in the Description page of Project Settings.


#include "HPBarTestActor.h"

#include "Blueprint/UserWidget.h"
#include "ShinobiBounce/HPBar/HPBarWidget.h"

// Sets default values
AHPBarTestActor::AHPBarTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHPBarTestActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (HPBarClass)
	{
		UHPBarWidget* HPWidget = CreateWidget<UHPBarWidget>(GetWorld(), HPBarClass);
		
		if (HPWidget)
		{
			HPWidget->AddToViewport();
			HPWidget->SetInitialHP(1000);
		}
	}
	
	
}

// Called every frame
void AHPBarTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

