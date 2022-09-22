// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactuable.generated.h"

UCLASS()
class INDIESPAINJAM_API AInteractuable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractuable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	UFUNCTION()
	void OnSliderValueChanged(float NewValue);
	UFUNCTION()
	void OnSliderMouseCaptureEnd();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	void OpenSlider();
	UFUNCTION(BlueprintCallable)
	void CloseSlider();
	UFUNCTION(BlueprintCallable)
	virtual void UpdatePercentile();

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> WidgetBlueprint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin="0.0", ClampMax="1.0"))
	float SliderValue;
	
private:
	UPROPERTY()
	APlayerController* PlayerController;
	UPROPERTY()
	UUserWidget* WidgetRef;
};
