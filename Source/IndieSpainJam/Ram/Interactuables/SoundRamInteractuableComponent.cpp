// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundRamInteractuableComponent.h"

#include "Kismet/GameplayStatics.h"

void USoundRamInteractuableComponent::BeginPlay()
{
	GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	Diff = MaxVolume - MinVolume;	
	SliderValue = GetSlideValue_Implementation();	
	Super::BeginPlay();
}

void USoundRamInteractuableComponent::OnSlideUpdated_Implementation(float slideValue)
{
	if (SoundMix == nullptr || SoundClass == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("SoundMix and SoundClass bad configured in SoundRamInteractuable of %s"), *GetOwner()->GetName());
		return;
	}
	if (GameInstance == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("MyGameInstance not found"));
		return;
	}
	Super::OnSlideUpdated_Implementation(slideValue);
	float volume = MinVolume + Diff * slideValue;
	GameInstance->MasterVolume = volume;
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), SoundMix, SoundClass, volume);
	UGameplayStatics::PushSoundMixModifier(GetWorld(), SoundMix);
}

float USoundRamInteractuableComponent::GetSlideValue_Implementation() const
{
	if (GameInstance == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("MyGameInstance not found"));
		return 0.0;
	}
	float volume = FMath::Clamp(GameInstance->MasterVolume, MinVolume, MaxVolume);
	return (volume - MinVolume) / Diff;
}

void USoundRamInteractuableComponent::Break()
{
	if (GameInstance == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("MyGameInstance not found"));
		return;
	}
	volumeBeforeBreak = GameInstance->MasterVolume;
	Fluctuate();
	Broken = true;
	UE_LOG(LogTemp, Display, TEXT("Broken Piece: %s"), *GetOwner()->GetName());
}

void USoundRamInteractuableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (IsBroken())
	{
		fluctuationCooldown -= DeltaTime;
		if (fluctuationCooldown <= 0)
		{
			Fluctuate();
		}
	}
}

float USoundRamInteractuableComponent::GetValidRandomVolume()
{
	float min = MinVolume;
	if (volumeBeforeBreak < MinVolume)
	{
		min = 0.0f;
	}
	return FMath::RandRange(min, volumeBeforeBreak);
}

void USoundRamInteractuableComponent::Fluctuate()
{
	fluctuationCooldown = BrokenFluctuationSeconds;
	OnSlideUpdated_Implementation(GetValidRandomVolume());
}

void USoundRamInteractuableComponent::OnActorClicked(AActor* Actor, FKey ButtonPressed)
{
	if(IsBroken())
	{
		Broken = false;
		GameInstance->BrokenPieces.Remove(this);
	}
	Super::OnActorClicked(Actor, ButtonPressed);
}
