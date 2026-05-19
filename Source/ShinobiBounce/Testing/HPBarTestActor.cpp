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
		HPBarInstance = CreateWidget<UHPBarWidget>(GetWorld(), HPBarClass);
		
		if (HPBarInstance)
		{
			HPBarInstance->AddToViewport();
			HPBarInstance->SetInitialHP(CurrentHP);
			HPBarInstance->SetAnchorsInViewport(FAnchors(0.f, 0.f));
			HPBarInstance->SetAlignmentInViewport(FVector2D(-0.9f, -0.4f));
			HPBarInstance->SetDesiredSizeInViewport(FVector2D(500.f, 100.f));
		}
	}
	
	
}

// Called every frame
void AHPBarTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// UE_LOG(LogTemp, Warning, TEXT("Tick: CurrentHP=%d, DepletionRate=%d, HPBarValid=%s"),
	//    CurrentHP,
	//    HPDepletionPerSecond,
	//    HPBarInstance ? TEXT("yes") : TEXT("no"));
	
	if (!HPBarInstance || CurrentHP <= 0) return;
	
	CurrentHP = FMath::Max(0.f, CurrentHP - HPDepletionPerSecond * DeltaTime);
	HPBarInstance->UpdateHP(CurrentHP);
}

