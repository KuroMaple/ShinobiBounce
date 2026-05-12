// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

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
	CollisionBox->SetBoxExtent(FVector(40.f, 7.f, 5.f));
	
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

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	FVector NewDirection = FVector(Direction.X, Direction.Y, 0.f).GetSafeNormal();
	ProjectileMovement->Velocity = NewDirection * this->InitialSpeed;
}

void AProjectile::OnBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity)
{
	if (BounceFromPaddleSfx)
	{
		UGameplayStatics::PlaySoundAtLocation(this, BounceFromPaddleSfx, ImpactResult.ImpactPoint);
	}
}


// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ProjectileMesh->AddLocalRotation(FRotator(0.f, 1.f, 0.f));
}

