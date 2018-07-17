

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StaticLogic.generated.h"

class UMyWay;
class UTwoDimensionalArray;
class AMyLevelScriptActor;

UCLASS()
class TESTWORK_API UStaticLogic : public UObject
{
	GENERATED_BODY()
	
public:

	UFUNCTION()
		static UMyWay* FindWay(FIntPoint Start, FIntPoint Finish, UTwoDimensionalArray* Map, AActor* WayOwner, AMyLevelScriptActor* Level);

	UFUNCTION()
		static FIntPoint FindClickPosition(float X, float Y);

	UFUNCTION()
		static FVector FindPositionFromPoint(FIntPoint Pos,float Z);

	UFUNCTION()
		static FIntPoint FindNextPoint(UMyWay* Way, FIntPoint CurrPoint);

private:

	static void InitMapForFind(UTwoDimensionalArray* Map);

	static bool StartWave(UTwoDimensionalArray* Map, TArray<FIntPoint>Start, FIntPoint StartPnt, FIntPoint Finish);

	static TArray<FIntPoint> FindWayFromMap(UTwoDimensionalArray* Map, FIntPoint Start, FIntPoint Finish, TArray<FIntPoint> Way);

};
