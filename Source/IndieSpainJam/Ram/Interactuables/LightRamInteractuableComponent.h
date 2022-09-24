// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RamInteractuableComponent.h"
#include "Engine/DirectionalLight.h"
#include "LightRamInteractuableComponent.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class INDIESPAINJAM_API ULightRamInteractuableComponent : public URamInteractuableComponent
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnSlideUpdated_Implementation(float slideValue) override;
	
public:
	UPROPERTY(EditAnywhere)
	ADirectionalLight* DirectionalLight;

	UPROPERTY(EditAnywhere)
	float MinIntensity = 0.0f;
	UPROPERTY(EditAnywhere)
	float MaxIntensity = 6.0f;

private:
	float Diff;
};
