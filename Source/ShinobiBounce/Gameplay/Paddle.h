// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "Paddle.generated.h"

class UInputAction;
class UCameraComponent;
class UInputMappingContext ;
class AProjectile;

UCLASS()
class SHINOBIBOUNCE_API APaddle : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APaddle();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> PaddleMesh;
	
	
	UPROPERTY(EditAnywhere, Category=Input)
	TObjectPtr<UInputAction> MovePaddleAction;
	
	void Move(const FInputActionValue& Value);
	
	UFUNCTION()
	void OnHitByProjectile(UPrimitiveComponent* HitComp, 
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit);
	
private:
	float MoveSpeed = 800.f;
	
	UPROPERTY()
	float MaxBounceAngle = 60.f;
	
};
