#pragma once

#include "RunnerSpawner.generated.h"

class URunnerSpawnerData;
class ARunnerObstacle;

USTRUCT(BlueprintType)
struct INDIESPAINJAM_API FRunnerObstacles
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<ARunnerObstacle>> RunnerObstacles;
	
}; // FRunnerObstacles

UCLASS(Abstract)
class ARunnerSpawner : public AActor
{
	GENERATED_BODY()
	
public:
	ARunnerSpawner();

	UFUNCTION(BlueprintCallable, Category = Spawner)
	void SpawnObstacle(const TSubclassOf<ARunnerObstacle>& obstacleClass, float slideThreshold);
	UFUNCTION(BlueprintCallable, Category = Spawner)
	void Run(URunnerSpawnerData* spawnData);
	UFUNCTION(BlueprintCallable, Category = Spawner)
	void DestroyObstacle(ARunnerObstacle* obstacle);
	UFUNCTION(BlueprintCallable, Category = Spawner)
	void ResetSpawner();
	UFUNCTION(BlueprintCallable, Category = Spawner)
	void SetObstaclesPaused(bool bPaused);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawner, Meta = (ClampMin = "0", Units = s))
	float WaitPlayerFailedTime = 1.5f;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Spawner)
	TMap<TSubclassOf<ARunnerObstacle>, FRunnerObstacles> AvailableObstacles;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Spawner)
	TMap<TSubclassOf<ARunnerObstacle>, FRunnerObstacles> RunningObstacles;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Spawner)
	bool bMaxObstaclesCap = true;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Spawner, Meta = (ClampMin = "1"))
	int32 MaxObstaclesCap = 10;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Spawner)
	int32 ObstaclesPassed = 0;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Spawner)
	TObjectPtr<URunnerSpawnerData> SpawnDataAsset = nullptr;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Spawner)
	int32 NextSpawnDataIdx = -1;

	UPROPERTY(BlueprintReadOnly, Category = Spawner)
	FTimerHandle NextObstacleTimer;

	FTimerHandle WaitPlayerFailedTimer;

	UFUNCTION(BlueprintImplementableEvent, Category = Spawner)
	void OnAllObstaclesPassed();
	UFUNCTION(BlueprintImplementableEvent, Category = Spawner)
	void OnPlayerFailed();
	UFUNCTION(BlueprintImplementableEvent, Category = Spawner)
	void OnEventTriggered(const FName& eventName);

	UFUNCTION()
	void OnObstacleHit(ARunnerObstacle* obstacle, bool bPlayerSuccess);

	void SpawnNextObstacle();
	
}; // ARunnerSpawner
