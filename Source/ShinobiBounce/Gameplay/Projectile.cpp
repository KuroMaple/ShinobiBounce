// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "Goal.h"
#include "Paddle.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox;
	CollisionBox->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	CollisionBox->SetBoxExtent(FVector(40.f, 4.f, 3.f));
	
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetupAttachment(RootComponent);
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->SetUpdatedComponent(CollisionBox);
	ProjectileMovement->ProjectileGravityScale = 0.f;
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->Bounciness = 1.f;
	ProjectileMovement->Friction = 0.f;
	ProjectileMovement->OnProjectileBounce.AddDynamic(this, &AProjectile::OnBounce);
	ProjectileMovement->bConstrainToPlane = true;
	ProjectileMovement->SetPlaneConstraintNormal(FVector(0.f, 0.f, 1.f));
	ProjectileMovement->bRotationFollowsVelocity = true;
	
	ProjectileMesh->SetRelativeRotation(FRotator(90.f, 180.f, 0.f));
	ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
}

void AProjectile::TriggerResizeAnimation()
{
	this->ProjectileMesh->SetRelativeScale3D(FVector(ProjectileBaseScale.X * 1.25, 
		ProjectileBaseScale.Y * 1.25, ProjectileBaseScale.Z * 1.25));
	
	GetWorldTimerManager().SetTimer(
		ResizeAnimTimerHandle,
		this,
		&AProjectile::RevertProjectileScale,
		ResizeAnimeTime,
		false
	);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileBaseScale = this->ProjectileMesh->GetRelativeScale3D();
	FVector NewDirection = FVector(Direction.X, Direction.Y, 0.f).GetSafeNormal();
	ProjectileMovement->Velocity = NewDirection * this->InitialSpeed;
}

void AProjectile::OnBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity)
{
	USoundBase* SelectedSfx = WallHitSfx;
	if (Cast<APaddle>(ImpactResult.GetActor()))
	{
		SelectedSfx = PaddleHitSfx;
	}
	
	TriggerResizeAnimation();
	
	UGameplayStatics::PlaySoundAtLocation(
		this, 
		SelectedSfx, 
		ImpactResult.ImpactPoint
		);
	
}

void AProjectile::RevertProjectileScale()
{
	this->ProjectileMesh->SetRelativeScale3D(ProjectileBaseScale);
}


// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Spinning Kunai
	const float CurrentSpeed = ProjectileMovement->Velocity.Size();
	const float SpeedRatio = FMath::Pow(CurrentSpeed / InitialSpeed, 1.f);
	ProjectileMesh->AddLocalRotation(FRotator(0.f, SpeedRatio, 0.f));
}

