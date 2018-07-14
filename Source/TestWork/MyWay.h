

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyWay.generated.h"

/**
 * 
 */
UCLASS()
class TESTWORK_API UMyWay : public UObject
{
	GENERATED_BODY()
	
public:

	UPROPERTY()
		TArray<FIntPoint> WayPoints;

	UPROPERTY()
		bool WayCyclical;

	UPROPERTY()
		bool MoveDirection;

	UPROPERTY()
		AActor* Owner;
	
};
