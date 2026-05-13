// Fill out your copyright notice in the Description page of Project Settings.


#include "Paddle.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "PongGameMode.h"
#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
// Sets default values
APaddle::APaddle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	PaddleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PaddleMesh"));
	RootComponent = PaddleMesh;
	
	// UE_LOG(LogTemp, Warning, TEXT("in paddle constructor"));
	
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	
}

void APaddle::BeginPlay()
{
	Super::BeginPlay();
	
	if (ShouldSetUpPlayerInput())
	{
		if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("EnhancedInput subsystem is NULL"));
			}
		}
	}
	
	PaddleMesh->OnComponentHit.AddDynamic(this, &APaddle::OnHitByProjectile);
}

void APaddle::Move(const FInputActionValue& Value)
{
	const float AxisValue = Value.Get<float>();
	const float Delta = AxisValue * MoveSpeed * GetWorld()->GetDeltaSeconds();
	const FVector Movement(0.f, Delta, 0.f);
	AddActorWorldOffset(Movement, true);
}

void APaddle::OnHitByProjectile(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (FMath::Abs(Hit.ImpactNormal.Y) > FMath::Abs(Hit.ImpactNormal.X))
	{
		return;  // side hit — ignore
	}
	
	AProjectile* Projectile = Cast<AProjectile>(OtherActor);
	if (!Projectile) return; // Don't apply paddle physics to non projectiles
	
	const float HitY = Hit.ImpactPoint.Y;
	const float PaddleY = GetActorLocation().Y;
	const float Offset = HitY - PaddleY; // distance of hit from center of paddle
	
	const float NormalizedOffset = Offset / PaddleMesh->Bounds.BoxExtent.Y;
	
	const float ClampedOffset = FMath::Clamp(NormalizedOffset, -1.f, 1.f);
	
	const float BounceAngleDegrees = ClampedOffset * MaxBounceAngle;
	
	const float CurrentProjectileSpeed = Projectile->ProjectileMovement->Velocity.Size();
	const float AngleRadians = FMath::DegreesToRadians(BounceAngleDegrees);
	
	const float SignX = FMath::Sign(Projectile->ProjectileMovement->Velocity.X) * -1.f;
	const float NewX = SignX * FMath::Cos(AngleRadians) * CurrentProjectileSpeed;
	const float NewY = FMath::Sin(AngleRadians) * CurrentProjectileSpeed;
	
	Projectile->ProjectileMovement->Velocity = FVector(NewX, NewY, 0.f);
	
	// Update projectile speed
	if (APongGameMode* GM = GetWorld()->GetAuthGameMode<APongGameMode>())
	{
		GM->OnPaddleHit(Projectile);
	}
}

void APaddle::UpdateMovement(float DeltaTime)
{
	// Base left empty in parent
}

// Called every frame
void APaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// UE_LOG(LogTemp, Warning, TEXT("%s Tick"), *GetName());
	UpdateMovement(DeltaTime);
}

// Called to bind functionality to input
void APaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// UE_LOG(LogTemp, Warning, TEXT("SetupPlayerInputComponent on %s"), *GetName());
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MovePaddleAction, ETriggerEvent::Triggered, this, &APaddle::Move);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Cast to EIC FAILED — project not using Enhanced Input"));
	}
}

