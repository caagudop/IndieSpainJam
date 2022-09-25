// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RamInteractuableComponent.h"
#include "IndieSpainJam/MyGameInstance.h"
#include "SoundRamInteractuableComponent.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class INDIESPAINJAM_API USoundRamInteractuableComponent : public URamInteractuableComponent
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnSlideUpdated_Implementation(float slideValue) override;
	virtual float GetSlideValue_Implementation() const override;
public:
	UPROPERTY(EditAnywhere)
	USoundMix* SoundMix;
	UPROPERTY(EditAnywhere)
	USoundClass* SoundClass;
	UPROPERTY(EditAnywhere)
	float MinVolume = 0;
	UPROPERTY(EditAnywhere)
	float MaxVolume = 1;

private:
	float Diff;
	UPROPERTY()
	UMyGameInstance* GameInstance;
};
