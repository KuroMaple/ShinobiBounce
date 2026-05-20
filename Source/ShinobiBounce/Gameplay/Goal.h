// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShinobiBounce/PongTypes.h"
#include "Goal.generated.h"

class UBoxComponent;

UCLASS()
class SHINOBIBOUNCE_API AGoal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGoal();
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> BoxComponent;
	
	UPROPERTY(EditAnywhere)
	EGoalSide Side = EGoalSide::Left;
	
	UFUNCTION()
	void OnGoalOverlap(UPrimitiveComponent* OverlappedComp,
					   AActor* OtherActor,
					   UPrimitiveComponent* OtherComp,
					   int32 OtherBodyIndex,
					   bool bFromSweep,
					   const FHitResult& SweepResult);

	

};
