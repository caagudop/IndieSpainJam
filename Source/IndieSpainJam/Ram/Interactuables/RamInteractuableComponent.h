// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "IndieSpainJam/MyGameInstance.h"
#include "IndieSpainJam/Ram/RamActor.h"
#include "IndieSpainJam/Ram/RAMInteractive.h"
#include "RamInteractuableComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INDIESPAINJAM_API URamInteractuableComponent : public UActorComponent, public IRAMInteractive
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URamInteractuableComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	bool Broken;
	UPROPERTY() UMyGameInstance* GameInstance;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	
	UFUNCTION() virtual void OnActorClicked(AActor* Actor, FKey ButtonPressed);
	virtual void Break();
	UFUNCTION(BlueprintCallable) bool IsBroken();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName PieceName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ARamActor* Ram;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin="0.0", ClampMax="1.0"))
	float SliderValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin="0.0", ClampMax="1.0"))
	float GoalValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin="0.0", ClampMax="1.0"))
	float ErrorMargin;
	virtual void OnSlideUpdated_Implementation(float slideValue) override;
	virtual float GetSlideValue_Implementation() const override;
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FReachedGoal);
	UPROPERTY(BlueprintAssignable)
	FReachedGoal OnReachedGoal;
	
private:
	bool HasReachedGoal();
};
