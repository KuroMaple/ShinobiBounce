// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "ShinobiBounce/PongTypes.h"
#include "Paddle.generated.h"

class UHPBarWidget;
class UInputAction;
class UCameraComponent;
class UInputMappingContext ;
class AProjectile;

UCLASS()
class SHINOBIBOUNCE_API APaddle : public APawn
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	
	UPROPERTY()
	TObjectPtr<UHPBarWidget> HPBar;
	
	UPROPERTY(EditDefaultsOnly, Category=UI)
	TSubclassOf<UHPBarWidget> HPBarWidgetClass;
	
	UPROPERTY(EditDefaultsOnly, Category=UI)
	FVector2D HPBarAnchor = FVector2D(0.f, 0.f);
	
	UPROPERTY(EditDefaultsOnly, Category=UI)
	FVector2D HPBarAlignment = FVector2D(-0.9f, -0.4f);
	
	UPROPERTY()
	int32 MaxHP = 750;
	
	int32 CurrentHP = 0;
	
	UPROPERTY()
	EGoalSide PaddleSide = EGoalSide::Left;
	
	// Sets default values for this pawn's properties
	APaddle();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void TakeDamage(int32 Amount);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> PaddleMesh;
	
	
	UPROPERTY(EditAnywhere, Category=Input)
	TObjectPtr<UInputAction> MovePaddleAction;
	
	void Move(const FInputActionValue& Value);
	
	UFUNCTION()
	virtual void OnHitByProjectile(UPrimitiveComponent* HitComp, 
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit);
	
	virtual void UpdateMovement(float DeltaTime);
	
	virtual bool ShouldSetUpPlayerInput() const { return true; }
	
	float MoveSpeed = 800.f;
	
private:
	
	
	UPROPERTY()
	float MaxBounceAngle = 45.f;
	
	void CreateHPBar();
	
};
