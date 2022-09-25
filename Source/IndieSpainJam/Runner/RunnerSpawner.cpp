#include "RunnerSpawner.h"

#include "RunnerObstacle.h"
#include "RunnerSpawnerData.h"

// ---------------------------------------------------------------------------------------------------------------------

ARunnerSpawner::ARunnerSpawner() : Super()
{
	PrimaryActorTick.bCanEverTick = false;
	
} // ARunnerSpawner

// ---------------------------------------------------------------------------------------------------------------------

void ARunnerSpawner::SpawnObstacle(const TSubclassOf<ARunnerObstacle>& obstacleClass, float slideThreshold)
{
	if (obstacleClass == nullptr)
	{
		return;
	}

	if (!AvailableObstacles.Contains(obstacleClass))
	{
		AvailableObstacles.Add(obstacleClass, {});
		RunningObstacles.Add(obstacleClass, {});
	}

	TArray<TObjectPtr<ARunnerObstacle>>& runnerObstacles = AvailableObstacles[obstacleClass].RunnerObstacles;
	if (runnerObstacles.IsEmpty())
	{
		runnerObstacles.Add(NewObject<ARunnerObstacle>(this, obstacleClass));
	}

	const TObjectPtr<ARunnerObstacle> obstacle = runnerObstacles.Last();
	runnerObstacles.Remove(obstacle);
	RunningObstacles[obstacleClass].RunnerObstacles.Add(obstacle);

	obstacle->SetSlideThreshold(slideThreshold);
	obstacle->SetActorTransform(GetActorTransform());
	obstacle->SetObstacleActive(true);
	
} // SpawnObstacle

// ---------------------------------------------------------------------------------------------------------------------

void ARunnerSpawner::Run(URunnerSpawnerData* spawnDataAsset)
{
	if (spawnDataAsset == nullptr)
	{
		return;
	}

	SpawnDataAsset = spawnDataAsset;
	NextSpawnDataIdx = 0;
	bMaxObstaclesCap = true;
	MaxObstaclesCap = spawnDataAsset->SpawnData.Num();
	
} // Run

// ---------------------------------------------------------------------------------------------------------------------

void ARunnerSpawner::DestroyObstacle(ARunnerObstacle* obstacle)
{
	if (obstacle == nullptr)
	{
		return;
	}

	obstacle->SetObstacleActive(false);
	const TSubclassOf<ARunnerObstacle> obstacleClass = obstacle->GetClass();
	RunningObstacles[obstacleClass].RunnerObstacles.Remove(obstacle);
	AvailableObstacles[obstacleClass].RunnerObstacles.Add(obstacle);
	
} // DestroyObstacle

// ---------------------------------------------------------------------------------------------------------------------

void ARunnerSpawner::ResetSpawner()
{
	for (TPair<TSubclassOf<ARunnerObstacle>, FRunnerObstacles>& obstaclesByType : RunningObstacles)
	{
		TArray<TObjectPtr<ARunnerObstacle>>& obstacles = obstaclesByType.Value.RunnerObstacles;
		while (!obstacles.IsEmpty())
		{
			DestroyObstacle(obstacles.Last());
		}
	}
	
} // ResetSpawner

// ---------------------------------------------------------------------------------------------------------------------

void ARunnerSpawner::SetObstaclesPaused(bool bPaused)
{
	for (const TPair<TSubclassOf<ARunnerObstacle>, FRunnerObstacles> obstaclesByType : RunningObstacles)
	{
		for (const TObjectPtr<ARunnerObstacle>& obstacle : obstaclesByType.Value.RunnerObstacles)
		{
			if (!obstacle.IsNull())
			{
				obstacle->SetActorTickEnabled(bPaused);
			}
		}
	}
	
} // SetObstaclesPaused

// ---------------------------------------------------------------------------------------------------------------------

void ARunnerSpawner::OnObstacleHit(ARunnerObstacle* obstacle, bool bPlayerSuccess)
{
	FTimerManager& timeMgr = GetWorldTimerManager();
	if (GetWorldTimerManager().IsTimerActive(WaitPlayerFailedTimer))
	{
		return;
	}
	
	if (bPlayerSuccess)
	{
		++ObstaclesPassed;
		if (bMaxObstaclesCap && ObstaclesPassed >= MaxObstaclesCap)
		{
			OnAllObstaclesPassed();
		}
	}
	else
	{
		GetWorldTimerManager().ClearTimer(NextObstacleTimer);
		SetObstaclesPaused(true);
		timeMgr.SetTimer(WaitPlayerFailedTimer, this, &ARunnerSpawner::OnPlayerFailed, WaitPlayerFailedTime);
	}
	
} // OnObstacleHit

// ---------------------------------------------------------------------------------------------------------------------

void ARunnerSpawner::SpawnNextObstacle()
{
	if (SpawnDataAsset.IsNull())
	{
		return;
	}

	const TArray<FObstacleSpawnData>& allSpawnData = SpawnDataAsset->SpawnData;
	if (NextSpawnDataIdx >= allSpawnData.Num())
	{
		return;
	}

	const FObstacleSpawnData& spawnData = allSpawnData[NextSpawnDataIdx];
	SpawnObstacle(spawnData.ObstacleType, spawnData.SlideThreshold);
	++NextSpawnDataIdx;

	if (spawnData.bDispatchEvent)
	{
		OnEventTriggered(spawnData.EventName);
	}

	if (spawnData.NextSpawn)
	{
		if (FMath::IsNearlyZero(spawnData.NextSpawn))
		{
			SpawnNextObstacle();
		}
		else
		{
			GetWorldTimerManager().SetTimer(NextObstacleTimer, this, &ARunnerSpawner::SpawnNextObstacle, spawnData.NextSpawn);
		}
	}
	
} // SpawnNextObstacle

// ---------------------------------------------------------------------------------------------------------------------
