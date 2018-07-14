#pragma once
#include "Object.h"
#include "Structs.generated.h"

USTRUCT()
struct FMyWay_ {

	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY()
		TArray<FIntPoint> WayPoints;

	UPROPERTY()
		bool WayCyclical;

	UPROPERTY()
		bool WayLenght;

	UPROPERTY()
		AActor* Owner;


};