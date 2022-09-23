// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractuableComp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INDIESPAINJAM_API UInteractuableComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractuableComp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UFUNCTION() void OnSliderValueChanged(float NewValue);
	UFUNCTION() void OnSliderMouseCaptureEnd();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable) void OpenSlider();
    UFUNCTION(BlueprintCallable) void CloseSlider();
    UFUNCTION(BlueprintCallable) bool HasReachedGoal();
	UFUNCTION(BlueprintCallable) virtual void UpdatePercentile();
    
    UPROPERTY(EditAnywhere) TSubclassOf<UUserWidget> WidgetBlueprint;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin="0.0", ClampMax="1.0"))
    float SliderValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin="0.0", ClampMax="1.0"))
	float GoalValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin="0.0", ClampMax="1.0"))
	float ErrorMargin;
	
private:
	UPROPERTY() APlayerController* PlayerController;
	UPROPERTY() UUserWidget* WidgetRef;
};
