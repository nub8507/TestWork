

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StaticLogic.generated.h"

/**
 * 
 */
UCLASS()
class TESTWORK_API UStaticLogic : public UObject
{
	GENERATED_BODY()
	
public:

	UFUNCTION()
		static void FindWay(FIntPoint Start, FIntPoint Finish);
	
	
};
