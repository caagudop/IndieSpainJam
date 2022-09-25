#pragma once

#include "RunnerSpawnerData.generated.h"

class ARunnerObstacle;

USTRUCT(BlueprintType)
struct INDIESPAINJAM_API FObstacleSpawnData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ARunnerObstacle> ObstacleType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ClampMin = "0", ClampMax = "100", Units = "%"))
	float SlideThreshold = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (InlineEditConditionToggle))
	bool bKeepSpawning = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (EditCondition = "bKeepSpawning", ClampMin = "0", Units = s))
	float NextSpawn = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (InlineEditConditionToggle))
	bool bDispatchEvent = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (EditCondition = "bKeepSpawning"))
	FName EventName;
	
}; // FObstacleSpawnData

UCLASS()
class INDIESPAINJAM_API URunnerSpawnerData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	TArray<FObstacleSpawnData> SpawnData;
	
}; // URunnerSpawnerData
