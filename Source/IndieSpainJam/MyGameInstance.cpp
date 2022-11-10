// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

#include "Ram/Interactuables/RamInteractuableComponent.h"

void UMyGameInstance::RegisterPiece(FName Name, URamInteractuableComponent* Piece)
{
	if (Pieces.Contains(Name))
	{
		UE_LOG(LogTemp, Error, TEXT("You cant register the same piece %s twice!"), *Piece->GetOwner()->GetName());
		return;		
	} 
	Pieces.Add(Name, Piece);
}

void UMyGameInstance::BreakPiece(FName Name)
{
	if (!Pieces.Contains(Name))
	{
		UE_LOG(LogTemp, Error, TEXT("You cant break unregistered piece %s!"), *Name.ToString());
		return;
	}
	URamInteractuableComponent* piece = Pieces.FindRef(Name);
	piece->Break();
	BrokenPieces.Add(piece);
}

void UMyGameInstance::BreakRandomPiece()
{
	if (Pieces.Num() < 0 || Pieces.Num() == BrokenPieces.Num())
	{
		return;
	}
	
	TArray<FName> componentNames;
	Pieces.GetKeys(componentNames);
	int32 pieceNumber = FMath::RandRange(0, componentNames.Num() - 1);
	while (Pieces[componentNames[pieceNumber]]->IsBroken())
	{
		pieceNumber = FMath::RandRange(0, componentNames.Num() - 1);
	}

	Pieces[componentNames[pieceNumber]]->Break();
	BrokenPieces.Add(Pieces[componentNames[pieceNumber]]);
	
} // BreakRandomPiece
