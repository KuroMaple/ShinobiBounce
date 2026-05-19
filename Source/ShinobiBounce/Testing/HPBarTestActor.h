// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HPBarTestActor.generated.h"

class UHPBarWidget;

UCLASS()
class SHINOBIBOUNCE_API AHPBarTestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHPBarTestActor();
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UHPBarWidget> HPBarClass;
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
