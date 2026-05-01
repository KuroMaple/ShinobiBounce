// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SBGameInstance.generated.h"

class USoundBase;
class UAudioComponent;

UENUM(BlueprintType)
enum class EMusicType : uint8
{
	Idle,
	Fight,
	Ending
};

USTRUCT(BlueprintType)
struct FSBTrack
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
	void PlayTrack(EMusicType Type, int32 Index);
	
	/**
	 * Plays CurrentTrackIndex if nothing is already playing
	 */
	UFUNCTION(BlueprintCallable, Category=Audio)
	void PlayIdleMusic();
	
	/**
	 * Stops current audio components playback
	 */
	UFUNCTION(BlueprintCallable, Category=Audio)
	void StopCurrentMusic();
	
	/**
	 * Controls audio component volume via private state
	 */
	UFUNCTION(BlueprintCallable, Category=Audio)
	void SetMusicVolume(float NewVolume);
	
	/**
	 * @return MusicVolume. For UI
	 */
	UFUNCTION(BlueprintPure, Category=Audio)
	float GetMusicVolume() const;
	
	/**
	 * @return CurrentTrackIndex. For UI
	 */
	UFUNCTION(BlueprintPure, Category=Audio)
	int32 GetCurrentTrackIndex(EMusicType Type) const;
	
	/**
	 * @return track display name
	 */
	UFUNCTION(BlueprintPure, Category=Audio)
	FText GetTrackDisplayName(EMusicType Type, int32 Index) const;

	/**
	 * @return Number of tracks
	 */
	UFUNCTION(BlueprintPure, Category=Audio)
	int32 GetTrackCount(EMusicType Type) const;
	
	UFUNCTION()
	void SetTrackIndex(EMusicType Type, int32 NewIndex);
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Audio)
	TArray<FSBTrack> IdleTracks;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Audio)
	TArray<FSBTrack> FightTracks;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Audio)
	TArray<FSBTrack> EndingTracks;
private:
	
	UPROPERTY()
	TObjectPtr<UAudioComponent> CurrentMusicComponent;
	
	float MusicVolume = 1.0f;
	int32 CurrentIdleTrackIndex = 0;
	int32 CurrentFightTrackIndex = 0;
	int32 CurrentEndingTrackIndex = 0;
	
	const TArray<FSBTrack>& GetTracks(EMusicType Type) const;
};
