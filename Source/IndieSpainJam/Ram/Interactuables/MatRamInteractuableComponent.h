// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RamInteractuableComponent.h"
#include "MatRamInteractuableComponent.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class INDIESPAINJAM_API UMatRamInteractuableComponent : public URamInteractuableComponent
{
	GENERATED_BODY()

protected:
    // Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnSlideUpdated_Implementation(float slideValue) override;
	
public:
	UPROPERTY(EditAnywhere)
	UMaterialInstanceDynamic* MaterialInstanceDynamic;
	UPROPERTY(EditAnywhere)
	FName ParameterName;
	UPROPERTY(EditAnywhere)
	float minValue;
	UPROPERTY(EditAnywhere)
	float maxValue;

private:
	float Diff;
};
