#pragma once

#include "IndieSpainJam/Ram/RAMInteractive.h"
#include "RunnerActor.generated.h"

class UBoxComponent;

UCLASS(Abstract)
class INDIESPAINJAM_API ARunnerActor : public AActor, public IRAMInteractive
{
	GENERATED_BODY()
	
public:
	ARunnerActor();

	virtual void OnConstruction(const FTransform& transform) override;
	
	void SetCurrentSlide(float slideValue);
	virtual void OnSlideUpdated_Implementation(float slideValue) override;
	virtual float GetSlideValue_Implementation() const override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnFailed();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
	TObjectPtr<UBoxComponent> Collision = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Runner)
	float MinSize = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Runner)
	float MaxSize = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Runner)
	float CurrentSlide = 0.5f;
	
}; // ARunnerActor
