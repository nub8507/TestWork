

#pragma once

#include "CoreMinimal.h"
#include "TwoDimensionalArray.generated.h"

UCLASS()
class TESTWORK_API UTwoDimensionalArray : public UObject
{
	GENERATED_BODY()

public:
	UTwoDimensionalArray();
	~UTwoDimensionalArray();

	FIntPoint Num();
	
	bool Set(int32 x, int32 y, int32 Val);

	int32 Get(int32 x, int32 y);

	void InitArray(int32 x, int32 y);

private:
	TArray<int32>Array;

	int32 SizeX;
	int32 SizeY;
};
