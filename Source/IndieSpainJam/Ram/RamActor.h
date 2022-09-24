// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RamActor.generated.h"


class URamInteractuableComponent;
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
	void OnReleased();
	void UpdateSelectorToMousePosition();
	
	float Length;
	bool IsSelectorDragged;
	UPROPERTY() TArray<TObjectPtr<UObject>> LinkedInteractives;
	UPROPERTY() APlayerController* PlayerController;
	
public:	 
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable) void LinkInteractive(UObject* interactive, bool bUpdateSlide = true);
	UFUNCTION(BlueprintCallable) void UnlinkInteractive(UObject* interactive);
	UFUNCTION(BlueprintCallable) void UnlinkAllInteractives();
	UFUNCTION(BlueprintCallable) void UpdateSlide(float slideValue);
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
	
protected:
	void UpdateInteractives();
	
};