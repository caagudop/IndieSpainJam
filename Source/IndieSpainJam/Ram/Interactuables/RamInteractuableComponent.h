// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "IndieSpainJam/Ram/RamActor.h"
#include "RamInteractuableComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INDIESPAINJAM_API URamInteractuableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URamInteractuableComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable) bool HasReachedGoal();
	UFUNCTION(BlueprintCallable) virtual void UpdatePercentile(float value);
	UFUNCTION() void OnActorClicked(AActor* Actor, FKey ButtonPressed);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ARamActor* Ram;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin="0.0", ClampMax="1.0"))
	float SliderValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin="0.0", ClampMax="1.0"))
	float GoalValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin="0.0", ClampMax="1.0"))
	float ErrorMargin;

};
