// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HPBarWidget.generated.h"

class UBorder;
class UHorizontalBox;
class USizeBox;
class UHPBarNibWidget;
/**
 * 
 */
UCLASS()
class SHINOBIBOUNCE_API UHPBarWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<USizeBox> HPBarSizeBox;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UHorizontalBox> NibContainer;
	
	// For runtime spawning
	UPROPERTY(EditDefaultsOnly, Category=HP)
	TSubclassOf<UHPBarNibWidget> NibWidgetClass;
	
	UPROPERTY()
	TArray<TObjectPtr<UHPBarNibWidget>> SpawnedNibs;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UBorder> HPMainBorder;
	
	UPROPERTY(EditDefaultsOnly, Category=Visual)
	TObjectPtr<UMaterialInterface> HPBorderMaterial;
	
	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> HPBorderMID;
	
	// Should take in Player or enemy actor to get its hp in future
	UFUNCTION(BlueprintCallable, Category=HP)
	void SetInitialHP(int32 HPAmount, int32 AbilityCharges);
	
	UFUNCTION()
	virtual void NativeConstruct() override;

	UFUNCTION()
	void UpdateHP(int32 HPAmount);
	
	void ConsumeNib(int32 ChargeCount);
private:
	int32 CurrentHp = 0;
	int32 MaxHP = 1000;
	float MaxHPBarWidth = 500.f;
	
	
	void UpdateMainBarWidth(int32 HPAmount);
	void EnsureNibCount(int32 TargetCount);
	void ActivateNibs();
};
