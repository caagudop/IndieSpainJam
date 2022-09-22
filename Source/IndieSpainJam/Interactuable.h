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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	void OpenSlider();
	UFUNCTION(BlueprintCallable)
	void CloseSlider();
	UFUNCTION(BlueprintCallable)
	virtual void UpdatePercentile();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* WidgetRef;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin="0.0", ClampMax="1.0"))
	float SliderValue;
	
private:
	APlayerController* PlayerController;
};
