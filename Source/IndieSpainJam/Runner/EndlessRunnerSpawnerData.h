#pragma once

#include "EndlessRunnerSpawnerData.generated.h"

class ARunnerObstacle;

USTRUCT(BlueprintType)
struct FObstacleEndlessSpawnerData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	TSubclassOf<ARunnerObstacle> ObstacleType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data, Meta = (ClampMin = "0", ClampMax = "100", Units = "%"))
	float MinSlideValue = 25.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data, Meta = (ClampMin = "0", ClampMax = "100", Units = "%"))
	float MaxSlideValue = 75.f;
	
}; // FComboObstacleSpawnData

USTRUCT(BlueprintType)
struct FComboObstacleSpawnData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	TArray<FObstacleEndlessSpawnerData> ObstaclesData;
	
}; // FComboObstacleSpawnData

UCLASS()
class UEndlessRunnerSpawnerData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	TArray<FComboObstacleSpawnData> ComboObstaclesData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data, Meta = (ClampMin = "0", Units = s))
	float MinSpawnTime = 4.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data, Meta = (ClampMin = "0", Units = s))
	float MaxSpawnTime = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data, Meta = (ClampMin = "0", Units = s))
	float WaitTimeUntilNewError = 10.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data, Meta = (ClampMin = "1"))
	int32 SpawnsNumToCheck = 3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data, Meta = (ClampMin = "0", Units = s))
	float AdditionalSpawnTime = 20.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data, Meta = (ClampMin = "0", ClampMax = "100", Units = "%"))
	float ErrorProbability = 25.f;
	
}; // UEndlessRunnerSpawnerData
