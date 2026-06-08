// Fill out your copyright notice in the Description page of Project Settings.


#include "PongGameMode.h"

#include "Paddle.h"
#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
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
	
	TArray<AActor*> Projectiles;
	UGameplayStatics::GetAllActorsOfClass(this, AProjectile::StaticClass(), Projectiles);
	if (Projectiles.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("No projectile found in level"));
	}
	else
	{
		if (Projectiles.Num() > 1)
		{
			UE_LOG(LogTemp, Error, TEXT("Multiple projectiles — aborting setup"));
			return;
		}
		ActiveProjectile = Cast<AProjectile>(Projectiles[0]);
	}
	
	TArray<AActor*> Paddles;
	UGameplayStatics::GetAllActorsOfClass(this, APaddle::StaticClass(), Paddles);
	
	for (AActor* A : Paddles)
	{
		APaddle* P = Cast<APaddle>(A);
		if (!P) continue; 
		
		switch (P->PaddleSide)
		{
			case EGoalSide::Left:  LeftPaddle  = P; break;
			case EGoalSide::Right: RightPaddle = P; break;
		}
	}
	
	if (!LeftPaddle || !RightPaddle)
	{
		UE_LOG(LogTemp, Error, TEXT("Missing paddle: Left=%s, Right=%s"),
			LeftPaddle ? TEXT("ok") : TEXT("NULL"),
			RightPaddle ? TEXT("ok") : TEXT("NULL"));
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
	// Reset project speed 
	if (ActiveProjectile && ActiveProjectile->ProjectileMovement)
	{
		const FVector CurrentVelocity = ActiveProjectile->ProjectileMovement->Velocity;
		ActiveProjectile->ProjectileMovement->Velocity = CurrentVelocity.GetSafeNormal() * ActiveProjectile->InitialSpeed;
	}
}

void APongGameMode::OnPaddleDefeated(APaddle* LosingPaddle)
{
	UE_LOG(LogTemp, Error, TEXT("APonggamemode::OnPaddleDefeated"));
	
	// TODO: Call on Defeat function of the paddle
	// e.g LosingPaddle->OnDefeat();
}

void APongGameMode::OnGoalHit(EGoalSide HitSide)
{
	APaddle* DamagedPaddle = (HitSide == EGoalSide::Left) ? LeftPaddle : RightPaddle;
	if (DamagedPaddle)
	{
		DamagedPaddle->TakeDamage(DamagePerHit);
		
	}
	
	ResetRally();
	RespawnProjectile(HitSide);
}

void APongGameMode::RespawnProjectile(EGoalSide HitSide)
{
	// TODO
}
