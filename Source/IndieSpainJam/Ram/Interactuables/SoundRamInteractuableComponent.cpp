// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundRamInteractuableComponent.h"

#include "Kismet/GameplayStatics.h"

void USoundRamInteractuableComponent::BeginPlay()
{
	GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	Diff = MaxVolume - MinVolume;	
	if (GameInstance == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("MyGameInstance not found"));
		return;
	}
	float volume = FMath::Clamp(GameInstance->MasterVolume, MinVolume, MaxVolume);
	SliderValue = (volume - MinVolume) / Diff;	
	Super::BeginPlay();
}

void USoundRamInteractuableComponent::OnSlideUpdated_Implementation(float slideValue)
{
	if (SoundMix == nullptr || SoundClass == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("SoundMix and SoundClass bad configured in SoundRamInteractuable of %s"), *GetOwner()->GetName());
	}
	if (GameInstance == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("MyGameInstance not found"));
		return;
	}
	float volume = MinVolume + Diff * slideValue;
	GameInstance->MasterVolume = volume;
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), SoundMix, SoundClass, volume);
	UGameplayStatics::PushSoundMixModifier(GetWorld(), SoundMix);
}