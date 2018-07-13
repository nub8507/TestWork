

#pragma once

#include "CoreMinimal.h"
#include "Structs.h"
#include "Engine/LevelScriptActor.h"
#include "MyLevelScriptActor.generated.h"

struct FMyWay;
class UTwoDimensionalArray;

UCLASS()
class TESTWORK_API AMyLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()
	
public:

	AMyLevelScriptActor();

	UFUNCTION()
		FMyWay FindWay(AActor* WayOwner);

	UFUNCTION()
		bool AddWay(FMyWay Way);

	UPROPERTY()
		UTwoDimensionalArray* Map;

private:

	UPROPERTY()
		TArray<FMyWay> WayList;
	
	
};
