// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HPBarNibWidget.generated.h"

class UImage;
/**
 * 
 */
UCLASS()
class SHINOBIBOUNCE_API UHPBarNibWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category=Visual)
	TObjectPtr<UMaterialInstance> ActiveMaterial;
	
	UFUNCTION(BlueprintCallable, Category=HP)
	void SetActive(bool bIsActive);
	
protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> NibImage;
};
