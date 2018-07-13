

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StaticLogic.generated.h"


class UTwoDimensionalArray;

UCLASS()
class TESTWORK_API UStaticLogic : public UObject
{
	GENERATED_BODY()
	
public:

	UFUNCTION()
		static void FindWay(FIntPoint Start, FIntPoint Finish, UTwoDimensionalArray* Map, AActor* WayOwner);
	
	
};
