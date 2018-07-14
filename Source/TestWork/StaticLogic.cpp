

#include "StaticLogic.h"

#include "TwoDimensionalArray.h"
#include "MyWay.h"

UMyWay* UStaticLogic::FindWay(FIntPoint Start, FIntPoint Finish, UTwoDimensionalArray* Map, AActor* WayOwner)
{
	//

	return nullptr;
	//
}

FIntPoint UStaticLogic::FindClickPosition(float X, float Y)
{
	//
	int32 iX, iY;
	//
	iX = (X) / 100.f;
	iY = (Y) / 100.f;
	//
	return FIntPoint(iX,iY);
	//
}

FVector UStaticLogic::FindPositionFromPoint(FIntPoint Pos)
{
	return FVector(Pos.X*100+50,Pos.Y*100+50,10);
}

FIntPoint UStaticLogic::FindNextPoint(UMyWay * Way, FIntPoint CurrPoint)
{
	//
	if (Way == nullptr)	return CurrPoint;
	//
	int StartPos, Direction, EndPos;
	//
	if (Way->MoveDirection) {
		StartPos = 0;
		Direction = 1;
		EndPos = Way->WayPoints.Num();
	}
	else {
		StartPos = Way->WayPoints.Num() - 1;
		Direction = -1;
		EndPos = Way->WayPoints.Num();
	}
	//
	for (int i = StartPos; -1 < i && i < EndPos; i = i + Direction) {
		if (Way->WayPoints[i] == CurrPoint){
			if (Way->MoveDirection) {
				if (i < Way->WayPoints.Num() - 1) { return Way->WayPoints[i + 1]; }
				else {
					if (Way->WayCyclical) {
						Way->MoveDirection = !Way->MoveDirection;
						return Way->WayPoints[Way->WayPoints.Num() - 2];
					}
					else { return CurrPoint; }
				}
			}
			else {
				if (i > 0) { return Way->WayPoints[i - 1]; }
				else {
					if (Way->WayCyclical) {
						Way->MoveDirection = !Way->MoveDirection;
						return Way->WayPoints[1];
					}
					else { return CurrPoint; }
				}
			}
		}
	}
	//
	return CurrPoint;
}
