
#include "MyLevelScriptActor.h"

#include "MyWay.h"
#include "TwoDimensionalArray.h"

bool AMyLevelScriptActor::AddWay(UMyWay* Way)
{
	if (Way == nullptr || Way->Owner == nullptr)
		return false;
	//
	UMyWay* T = this->FindWay(Way->Owner);
	if (T->Owner == nullptr)
		WayList.Add(Way);
	//
	return true;
}

AMyLevelScriptActor::AMyLevelScriptActor()
{
	this->Map = NewObject<UTwoDimensionalArray>();
	this->Map->InitArray(31, 31);
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
