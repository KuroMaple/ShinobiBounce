// Fill out your copyright notice in the Description page of Project Settings.


#include "SBGameInstance.h"

#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"


void USBGameInstance::PlayTrack(int32 Index)
{
	if (!IdleTracks.IsValidIndex(Index) || !IdleTracks[Index].Sound) return;
	
	StopMenuMusic();
	
	MenuMusicComponent = UGameplayStatics::SpawnSound2D(
		this,
		IdleTracks[Index].Sound,
		MusicVolume,
		1.0f,
		0.0f,
		nullptr,
		true,
		true
		);
	
	CurrentTrackIndex = Index;
}

void USBGameInstance::PlayMenuMusic()
{
	if (MenuMusicComponent && MenuMusicComponent->IsPlaying()) return;
	PlayTrack(CurrentTrackIndex);
	
}

void USBGameInstance::StopMenuMusic()
{
	if (MenuMusicComponent)
	{
		MenuMusicComponent->Stop();
	}
}

void USBGameInstance::SetMusicVolume(float NewVolume)
{
	MusicVolume = FMath::Clamp(NewVolume, 0.0f, 1.0f);
	if (MenuMusicComponent)
	{
		MenuMusicComponent->SetVolumeMultiplier(MusicVolume);
	}
}

float USBGameInstance::GetMusicVolume() const
{
	return MusicVolume;
}

int32 USBGameInstance::GetCurrentTrackIndex() const
{
	return CurrentTrackIndex;
}

FText USBGameInstance::GetTrackDisplayName(int32 Index) const
{
	return IdleTracks.IsValidIndex(Index) ? IdleTracks[Index].DisplayName : FText::GetEmpty();
}

int32 USBGameInstance::GetTrackCount() const
{
	return IdleTracks.Num();
}
