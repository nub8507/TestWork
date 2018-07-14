

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StaticLogic.generated.h"

class UMyWay;
class UTwoDimensionalArray;

UCLASS()
class TESTWORK_API UStaticLogic : public UObject
{
	GENERATED_BODY()
	
public:

	UFUNCTION()
		static UMyWay* FindWay(FIntPoint Start, FIntPoint Finish, UTwoDimensionalArray* Map, AActor* WayOwner);
	
	UFUNCTION()
		static FIntPoint FindClickPosition(float X, float Y);

	UFUNCTION()
		static FVector FindPositionFromPoint(FIntPoint Pos);

	UFUNCTION()
		static FIntPoint FindNextPoint(UMyWay* Way, FIntPoint CurrPoint);

};
