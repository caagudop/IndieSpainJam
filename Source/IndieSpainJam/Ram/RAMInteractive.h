#pragma once

#include "RAMInteractive.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class URAMInteractive : public UInterface
{
	GENERATED_BODY()
	
}; // URAMInteractive

class INDIESPAINJAM_API IRAMInteractive
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void OnSlideUpdated(float slideValue);

	UFUNCTION(BlueprintNativeEvent)
	float GetSlideValue() const;
	
}; // URAMInteractive