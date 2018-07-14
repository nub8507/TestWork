

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "MyLevelScriptActor.generated.h"

class UMyWay;
class UTwoDimensionalArray;

UCLASS()
class TESTWORK_API AMyLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()
	
public:

	AMyLevelScriptActor();

	UFUNCTION()
		UMyWay* FindWay(AActor* WayOwner);

	UFUNCTION()
		bool AddWay(UMyWay* Way);

	UPROPERTY()
		UTwoDimensionalArray* Map;

private:

	UPROPERTY()
		TArray<UMyWay*> WayList;
	
	
};
