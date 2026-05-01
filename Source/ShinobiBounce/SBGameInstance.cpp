// Fill out your copyright notice in the Description page of Project Settings.


#include "SBGameInstance.h"

#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"


void USBGameInstance::PlayTrack(EMusicType Type, int32 Index)
{
	
	const TArray<FSBTrack>& Tracks = GetTracks(Type);
	if (!Tracks.IsValidIndex(Index) || !Tracks[Index].Sound) return;
	
	StopCurrentMusic();
	
	const bool bPersistAcrossLevels = (Type == EMusicType::Idle); // Only idle music should persist everywhere
	CurrentMusicComponent = UGameplayStatics::SpawnSound2D(
		this,
		Tracks[Index].Sound,
		MusicVolume,
		1.0f,
		0.0f,
		nullptr,
		bPersistAcrossLevels,
		true
		);
	
	switch (Type)
	{
		case EMusicType::Idle:   CurrentIdleTrackIndex   = Index; break;
		case EMusicType::Fight:  CurrentFightTrackIndex  = Index; break;
		case EMusicType::Ending: CurrentEndingTrackIndex = Index; break;
	}
}

void USBGameInstance::PlayIdleMusic()
{
	PlayTrack(EMusicType::Idle, CurrentIdleTrackIndex);
}

void USBGameInstance::StopCurrentMusic()
{
	if (CurrentMusicComponent)
	{
		CurrentMusicComponent->Stop();
	}
}

void USBGameInstance::SetMusicVolume(float NewVolume)
{
	MusicVolume = FMath::Clamp(NewVolume, 0.0f, 1.0f);
	if (CurrentMusicComponent)
	{
		CurrentMusicComponent->SetVolumeMultiplier(MusicVolume);
	}
}

float USBGameInstance::GetMusicVolume() const
{
	return MusicVolume;
}

int32 USBGameInstance::GetCurrentTrackIndex(EMusicType Type) const
{
	switch (Type)
	{
	case EMusicType::Idle:
		return CurrentIdleTrackIndex;
	case EMusicType::Fight:
		return CurrentFightTrackIndex;
	case EMusicType::Ending:
		return CurrentEndingTrackIndex;
	default:
		checkNoEntry();
		return CurrentIdleTrackIndex;
	}
}

FText USBGameInstance::GetTrackDisplayName(EMusicType Type, int32 Index) const
{
	const TArray<FSBTrack>& Tracks = GetTracks(Type);
	return Tracks.IsValidIndex(Index) ? Tracks[Index].DisplayName : FText::GetEmpty();
}

int32 USBGameInstance::GetTrackCount(EMusicType Type) const
{
	return GetTracks(Type).Num();
}

void USBGameInstance::SetTrackIndex(EMusicType Type, int32 NewIndex)
{
	switch (Type)
	{
	case EMusicType::Idle:   CurrentIdleTrackIndex   = NewIndex; break;
	case EMusicType::Fight:  CurrentFightTrackIndex  = NewIndex; break;
	case EMusicType::Ending: CurrentEndingTrackIndex = NewIndex; break;
	default: checkNoEntry();
	}
}

const TArray<FSBTrack>& USBGameInstance::GetTracks(EMusicType Type) const
{
	switch (Type)
	{
		case EMusicType::Idle:
			return IdleTracks;
		case EMusicType::Fight:
			return FightTracks;
		case EMusicType::Ending:
			return EndingTracks; 
		default:
			checkNoEntry();
			return IdleTracks;
	}
}
