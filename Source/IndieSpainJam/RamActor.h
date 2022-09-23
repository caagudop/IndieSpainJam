// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractuableComp.h"
#include "GameFramework/Actor.h"
#include "RamActor.generated.h"


UENUM(BlueprintType)
enum class ELockAxis : uint8
{
	X UMETA(DisplayName = "X"),
	Y UMETA(DisplayName = "Y")
};

UCLASS()
class INDIESPAINJAM_API ARamActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARamActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void SyncActorAxis(USceneComponent* Component, UPrimitiveComponent* From);
	float GetLightAbs(float value);
	UFUNCTION() void OnSelectorClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);
	UFUNCTION() void OnSelectorReleased(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);
	void UpdateSelectorToMousePosition();
	
	float Length;
	bool IsSelectorDragged;
	UPROPERTY() UInteractuableComp* CurrentInteractuable;
	UPROPERTY() APlayerController* PlayerController;
	
public:	 
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable) void LinkInteractuable(UInteractuableComp* interactuable);
	UFUNCTION(BlueprintCallable) void UnlinkInteractuable();
	UFUNCTION(BlueprintCallable) float GetValue();

	UPROPERTY(EditAnywhere) ELockAxis LockAxis;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* Root;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* Origin;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* Destination;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Selector;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (MakeEditWidget))
	FVector Test;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (MakeEditWidget))
	FTransform TestTr;
	
};