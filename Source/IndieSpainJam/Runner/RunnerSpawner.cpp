#include "RunnerSpawner.h"

#include "EndlessRunnerSpawnerData.h"
#include "RunnerObstacle.h"
#include "RunnerSpawnerData.h"
#include "IndieSpainJam/MyGameInstance.h"

// ---------------------------------------------------------------------------------------------------------------------

ARunnerSpawner::ARunnerSpawner() : Super()
{
	PrimaryActorTick.bCanEverTick = false;
	
} // ARunnerSpawner

// ---------------------------------------------------------------------------------------------------------------------

ARunnerObstacle* ARunnerSpawner::SpawnObstacle(const TSubclassOf<ARunnerObstacle>& obstacleClass, float slideThreshold)
{
	if (obstacleClass == nullptr)
	{
		return nullptr;
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
	return obstacle;
	
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
	SpawnNextObstacle();
	
} // Run

// ---------------------------------------------------------------------------------------------------------------------

void ARunnerSpawner::RunEndless(UEndlessRunnerSpawnerData* spawnData)
{
	if (spawnData == nullptr)
	{
		return;
	}

	EndlessSpawnDataAsset = spawnData;
	SpawnDataAsset = nullptr;
	NextSpawnDataIdx = -1;
	bMaxObstaclesCap = false;
	SpawnNextEndlessObstacle();
	
} // RunEndless

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
		else if (SendErrorObstacle != nullptr)
		{
			SendErrorObstacle->Reset();
			if (UMyGameInstance* gameInstance = Cast<UMyGameInstance>(GetGameInstance()))
			{
				gameInstance->BreakRandomPiece();
			}

			FTimerManager& timeManager = GetWorldTimerManager();
			timeManager.SetTimer(NextObstacleTimer, this, &ARunnerSpawner::SpawnNextEndlessObstacle,
				EndlessSpawnDataAsset->AdditionalSpawnTime);
			timeManager.SetTimer(WaitToNextError, EndlessSpawnDataAsset->WaitTimeUntilNewError, false);
			
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

void ARunnerSpawner::SpawnNextEndlessObstacle()
{
	if (EndlessSpawnDataAsset.IsNull())
	{
		return;
	}


	LastObstacleClass;
	EndlessSpawnDataAsset->ComboObstaclesData
	
	static constexpr int32 MAX_CONSECUTIVE_OBSTACLES = 3;
	if (ConsecutiveObstacles >= MAX_CONSECUTIVE_OBSTACLES)
	{
		
	}

	ARunnerObstacle* lastObstacle = nullptr;
	for (const FObstacleEndlessSpawnerData& obstacle : EndlessSpawnDataAsset->ComboObstaclesData[idx].ObstaclesData)
	{
		lastObstacle = SpawnObstacle(obstacle.ObstacleType, FMath::RandRange(obstacle.MinSlideValue, obstacle.MaxSlideValue));
	}
	++EndlessObstaclesSpawned;
	
	if (!GetWorldTimerManager().IsTimerActive(WaitToNextError) && EndlessSpawnDataAsset.IsNull() &&
		EndlessObstaclesSpawned > 0 && EndlessObstaclesSpawned % EndlessSpawnDataAsset->SpawnsNumToCheck == 0 &&
		100.f * FMath::RandRange(0.f, 1.f) <= EndlessSpawnDataAsset->ErrorProbability)
	{
		SendErrorObstacle = lastObstacle;
	}
	else
	{
		const float nextSpawnTime = FMath::RandRange(EndlessSpawnDataAsset->MinSpawnTime, EndlessSpawnDataAsset->MaxSpawnTime);
		GetWorldTimerManager().SetTimer(NextObstacleTimer, this, &ARunnerSpawner::SpawnNextEndlessObstacle, nextSpawnTime);
	}
	
} // SpawnNextEndlessObstacle

// ---------------------------------------------------------------------------------------------------------------------
