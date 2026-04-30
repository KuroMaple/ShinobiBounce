// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SBGameInstance.generated.h"

class USoundBase;
class UAudioComponent;

USTRUCT(BlueprintType)
struct FIdleTrack
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Audio)
	TObjectPtr<USoundBase> Sound;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Audio)
	FText DisplayName;	
};

/**
 * 
 */
UCLASS()
class SHINOBIBOUNCE_API USBGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	/**
	 * Called by options menu arrows, used to preview tracks 
	 */
	UFUNCTION(BlueprintCallable, Category=Audio)
	void PlayTrack(int32 Index);
	
	/**
	 * Plays CurrentTrackIndex if nothing is already playing
	 */
	UFUNCTION(BlueprintCallable, Category=Audio)
	void PlayMenuMusic();
	
	/**
	 * Stops current audio components playback
	 */
	UFUNCTION(BlueprintCallable, Category=Audio)
	void StopMenuMusic();
	
	/**
	 * Controls audio component volume via private state
	 */
	UFUNCTION(BlueprintCallable, Category=Audio)
	void SetMusicVolume(float NewVolume);
	
	/**
	 * Returns MusicVolume. For UI
	 */
	UFUNCTION(BlueprintPure, Category=Audio)
	float GetMusicVolume() const;
	
	/**
	 * @return CurrentTrackIndex. For UI
	 */
	UFUNCTION(BlueprintPure, Category=Audio)
	int32 GetCurrentTrackIndex() const;
	
	
	/**
	 * @return track display name
	 */
	UFUNCTION(BlueprintPure, Category=Audio)
	FText GetTrackDisplayName(int32 Index) const;

	/**
	 * @return Number of tracks
	 */
	UFUNCTION(BlueprintPure, Category=Audio)
	int32 GetTrackCount() const;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Audio)
	TArray<FIdleTrack> IdleTracks;
	
private:
	
	UPROPERTY()
	TObjectPtr<UAudioComponent> MenuMusicComponent;
	
	float MusicVolume = 1.0f;
	int32 CurrentTrackIndex = 0;
};
