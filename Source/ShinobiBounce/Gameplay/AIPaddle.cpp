// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPaddle.h"

#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

AAIPaddle::AAIPaddle()
{
	AutoPossessPlayer = EAutoReceiveInput::Disabled;
}

void AAIPaddle::BeginPlay()
{
	
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("AI Paddle begin play"));
	TArray<AActor*> Found;
	UGameplayStatics::GetAllActorsOfClass(this, AProjectile::StaticClass(), Found);
	if (Found.Num() > 0)
	{
		TrackedProjectile = Cast<AProjectile>(Found[0]); // Assumes there's only one projectile for now
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to find projectile"));
	}
}

void AAIPaddle::UpdateMovement(float DeltaTime)
{
	Super::UpdateMovement(DeltaTime);
	UE_LOG(LogTemp, Warning, TEXT("AI UpdateMovement firing"));
	if (!IsValid(TrackedProjectile)) return;
	
	const float DifferenceY = TrackedProjectile->GetActorLocation().Y - GetActorLocation().Y;
	if (FMath::Abs(DifferenceY) <= DeadzoneRadius) return;
	const float MaxStep = MoveSpeed * DeltaTime;
	const float MoveStep = FMath::Clamp(DifferenceY, -MaxStep, +MaxStep);
	
	AddActorWorldOffset(FVector(0, MoveStep, 0), true);
}
