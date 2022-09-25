#pragma once

#include "RunnerObstacle.generated.h"

class UBoxComponent;
UCLASS(Abstract)
class INDIESPAINJAM_API ARunnerObstacle : public AActor
{
	GENERATED_BODY()
	
public:
	ARunnerObstacle();
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnObstacleHit, ARunnerObstacle*, obstacle, bool, bPlayerSuccess);
	UPROPERTY(BlueprintAssignable, Category = Obstacle)
	FOnObstacleHit OnObstacleHit;

	virtual void PostInitializeComponents() override;
	virtual void Tick(float deltaSeconds) override;
	
	FORCEINLINE void SetSlideThreshold(float slideThreshold) { SlideThreshold = slideThreshold; }
	
	UFUNCTION(BlueprintCallable, Category = Obstacle)
	void SetObstacleActive(bool bActive);
	
	virtual void NotifyHit(UPrimitiveComponent* myComp, AActor* other, UPrimitiveComponent* otherComp, bool bSelfMoved,
		FVector hitLocation, FVector hitNormal, FVector normalImpulse, const FHitResult& hit) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> CollisionTrigger = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Obstacle, Meta = (ClampMin = "0.01", Units = "m/s"))
	float Speed = 2.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Obstacle, Meta = (ClampMin = "0", ClampMax = "100", Units = "%"))
    float SlideThreshold = 50.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Obstacle)
	bool bFailIfBelowThreshold = false;
	
}; // ARunnerObstacle
