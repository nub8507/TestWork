
#include "MyLevelScriptActor.h"

#include "MyWay.h"
#include "TwoDimensionalArray.h"

bool AMyLevelScriptActor::AddWay(UMyWay* Way)
{
	if (Way == nullptr || Way->Owner == nullptr)
		return false;
	//
	UMyWay* T = this->FindWay(Way->Owner);
	if (T == nullptr)
		WayList.Add(Way);
	//
	return true;
}

void AMyLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();
	//
	this->Map = NewObject<UTwoDimensionalArray>();
	this->Map->InitArray(31, 31);
	//
}

AMyLevelScriptActor::AMyLevelScriptActor()
{

}

UMyWay* AMyLevelScriptActor::FindWay(AActor* WayOwner)
{
	if (WayOwner == nullptr)
		return nullptr;
	//
	int T = this->WayList.Num();
	for (int i = 0; i < T; i++) {
		if (this->WayList[i]->Owner == WayOwner)
			return this->WayList[i];
	}
	return nullptr;
}
