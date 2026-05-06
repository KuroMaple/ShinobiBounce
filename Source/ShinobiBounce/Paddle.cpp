// Fill out your copyright notice in the Description page of Project Settings.


#include "Paddle.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
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
	
	UE_LOG(LogTemp, Warning, TEXT("in paddle constructor"));
	
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	
}

// Called when the game starts or when spawned
void APaddle::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			// Add the context with a priority (higher values take precedence)
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
			UE_LOG(LogTemp, Error, TEXT("IMC Added"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("PaddleMappingContext is NULL"));
		}
	}
}

void APaddle::Move(const FInputActionValue& Value)
{
	const float AxisValue = Value.Get<float>();
	const float Delta = AxisValue * MoveSpeed * GetWorld()->GetDeltaSeconds();
	const FVector Movement(0.f, Delta, 0.f);
	AddActorWorldOffset(Movement, true);
}

// Called every frame
void APaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MovePaddleAction, ETriggerEvent::Triggered, this, &APaddle::Move);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Cast to EIC FAILED — project not using Enhanced Input"));
	}
}

