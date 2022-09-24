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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInstanceDynamic* MaterialInstanceDynamic;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ParameterName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float minValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float maxValue;

private:
	float Diff;
};
