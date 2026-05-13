// Fill out your copyright notice in the Description page of Project Settings.


#include "PongGameMode.h"

#include "Paddle.h"
#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
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

void APongGameMode::OnPaddleHit(AProjectile* Projectile)
{
	if (!Projectile || !Projectile->ProjectileMovement) return;
	
	RallyHitCount++;
	
	const float CurrentSpeed = Projectile->ProjectileMovement->Velocity.Size();
	const float NewSpeed = FMath::Min(CurrentSpeed * SpeedIncreasePerHit, MaxSpeed);
	
	Projectile->ProjectileMovement->Velocity = Projectile->ProjectileMovement->Velocity.GetSafeNormal() * NewSpeed;
}

void APongGameMode::ResetRally()
{
	RallyHitCount = 0;
}
