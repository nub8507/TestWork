
#include "MyLevelScriptActor.h"

#include "TwoDimensionalArray.h"

bool AMyLevelScriptActor::AddWay(FMyWay Way)
{
	if (Way.Owner==nullptr)
		return false;
	//
	FMyWay T = this->FindWay(Way.Owner);
	if (T.Owner == nullptr)
		WayList.Add(Way);
	//
	return true;
}

AMyLevelScriptActor::AMyLevelScriptActor()
{
	this->Map = NewObject<UTwoDimensionalArray>();
	this->Map->InitArray(31, 31);
}

FMyWay AMyLevelScriptActor::FindWay(AActor* WayOwner)
{
	if (WayOwner == nullptr)
		return FMyWay();
	//
	int T = this->WayList.Num();
	for (int i = 0; i < T; i++) {
		if (this->WayList[i].Owner == WayOwner)
			return this->WayList[i];
	}
	return FMyWay();
}
