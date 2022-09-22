// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractuableComp.h"
#include "ChairInteractuableComp.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class INDIESPAINJAM_API UChairInteractuableComp : public UInteractuableComp
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void UpdatePercentile() override;

public:
	UPROPERTY(EditAnywhere)
	FVector MinScale = FVector(0,0, 0);
	UPROPERTY(EditAnywhere)
	FVector MaxScale = FVector(1,1, 1);

private:
	float XDiff;
	float YDiff;
	float ZDiff;
};
