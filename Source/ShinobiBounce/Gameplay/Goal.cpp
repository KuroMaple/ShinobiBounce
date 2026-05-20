// Fill out your copyright notice in the Description page of Project Settings.


#include "Goal.h"

#include "PongGameMode.h"
#include "Projectile.h"
#include "Components/BoxComponent.h"

// Sets default values
AGoal::AGoal()
{
	PrimaryActorTick.bCanEverTick = false;
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;
	
	BoxComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	BoxComponent->SetBoxExtent(FVector(50.f, 700.f, 100.f));
	
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AGoal::OnGoalOverlap);
}


void AGoal::OnGoalOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!Cast<AProjectile>(OtherActor)) return;   // only react to projectiles

	if (APongGameMode* GM = GetWorld()->GetAuthGameMode<APongGameMode>())
	{
		GM->OnGoalHit(Side);
	}
}



