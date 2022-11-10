// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

class URamInteractuableComponent;
/**
 * 
 */
UCLASS()
class INDIESPAINJAM_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void RegisterPiece(FName Name, URamInteractuableComponent* Piece);
	UFUNCTION(BlueprintCallable)
	void BreakRandomPiece();
	UFUNCTION(BlueprintCallable)
	void BreakPiece(FName Name);

	UPROPERTY(BlueprintReadWrite)
	float MasterVolume = 1;
	UPROPERTY() TArray<URamInteractuableComponent*> BrokenPieces;
	
private:
	
	UPROPERTY() TMap<FName,URamInteractuableComponent*> Pieces;
	
};
