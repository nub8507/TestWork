

#include "StaticLogic.h"

#include "TwoDimensionalArray.h"
#include "MyWay.h"
#include "MyLevelScriptActor.h"

UMyWay* UStaticLogic::FindWay(FIntPoint Start, FIntPoint Finish, UTwoDimensionalArray* Map, AActor* WayOwner, AMyLevelScriptActor* Level)
{
	//
	if (Level == nullptr || WayOwner == nullptr) return nullptr;
	//
	UMyWay* Way;
	//
	Way = Level->FindWay(WayOwner);
	//
	if(Way == nullptr) {
		Way= NewObject<UMyWay>();
		Way->WayCyclical = false;
		Way->MoveDirection = true;
		Way->Owner = WayOwner;
		Level->AddWay(Way);
	}else
		Way->WayPoints.Empty();
	//
	if (Start == Finish || Map == nullptr||Map->IsEmpty()) {
		Way->WayPoints.Empty();
		return Way;
	}
	//
	InitMapForFind(Map);
	//
	TArray<FIntPoint>StartPos;
	StartPos.Empty();
	StartPos.Add(Start);
	//
	if (!StartWave(Map, StartPos, Start, Finish)) {
		Way->WayPoints.Empty();
		return Way;
	}
	//
	StartPos.Empty();
	//
	Way->WayPoints = FindWayFromMap(Map, Start, Finish, Way->WayPoints);
	//
	return Way;
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

FVector UStaticLogic::FindPositionFromPoint(FIntPoint Pos,float Z)
{
	return FVector(Pos.X*100+50,Pos.Y*100+50,Z);
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

void UStaticLogic::InitMapForFind(UTwoDimensionalArray* Map)
{
	//
	for (int i = 0; i < 31; i++) {
		for (int j = 0; j < 31; j++) {
			if (Map->Get(i, j) != -1) {
				Map->Set(i, j, 0);
			}
		}
	}
	//
}

bool UStaticLogic::StartWave(UTwoDimensionalArray * Map, TArray<FIntPoint> Start, FIntPoint StartPnt, FIntPoint Finish)
{
	//
	if (Start.Num() == 0) return false;
	//
	TArray<FIntPoint>StartPos;
	StartPos.Empty();
	//
	for (int k = 0; k < Start.Num(); k++) {
		int32 NumWave = Map->Get(Start[k].X, Start[k].Y);
		if (Start[k] == Finish) return true;
		//
		int32 X = Start[k].X;
		int32 Y = Start[k].Y;
		//
		if (X >= 1 ) {
			int32 Sel = Map->Get(X - 1, Y);
			if (Sel == 0 && StartPnt != FIntPoint(X - 1, Y)) {
				StartPos.Add(FIntPoint(X - 1, Y));
				Map->Set(X - 1, Y, NumWave + 1);
			}
		}
		if (X <= Map->RetMapSize().X-2) {
			int32 Sel = Map->Get(X + 1, Y );
			if (Sel == 0 && StartPnt != FIntPoint(X + 1, Y)) {
				StartPos.Add(FIntPoint(X + 1, Y));
				Map->Set(X + 1, Y, NumWave + 1);
			}
		}
		if ( Y <= Map->RetMapSize().Y - 2) {
			int32 Sel = Map->Get(X , Y + 1);
			if (Sel == 0 && StartPnt != FIntPoint(X, Y + 1)) {
				StartPos.Add(FIntPoint(X , Y + 1));
				Map->Set(X, Y + 1, NumWave + 1);
			}
		}
		if (Y >= 1) {
			int32 Sel = Map->Get(X , Y - 1);
			if (Sel == 0 && StartPnt != FIntPoint(X, Y - 1)) {
				StartPos.Add(FIntPoint(X, Y - 1));
				Map->Set(X , Y - 1, NumWave + 1);
			}
		}
		//
	}
	//
	Start.Empty();
	//
	return StartWave(Map, StartPos, StartPnt, Finish);
}

TArray<FIntPoint> UStaticLogic::FindWayFromMap(UTwoDimensionalArray * Map, FIntPoint Start, FIntPoint Finish, TArray<FIntPoint> Way)
{
	//
	int X, Y;
	X = Finish.X;
	Y = Finish.Y;
	//
	Way.Insert(Finish, 0);
	//
	if (Start == Finish) return Way;
	//
	FIntPoint NewFinish;
	int32 MinWave;
	//
	MinWave = Map->Get(Finish.X, Finish.Y);
	//
	if (X >= 1) {
		int32 Sel = Map->Get(X - 1, Y);
		if (Sel != -1 && (Sel != 0 || FIntPoint(X - 1, Y) == Start)) {
			if (MinWave > Sel){
				NewFinish = FIntPoint(X - 1, Y);
				MinWave = Sel;
			}
		}
	}
	if (X <= Map->RetMapSize().X - 2 ) {
		int32 Sel = Map->Get(X + 1, Y);
		if (Sel != -1 && (Sel != 0 || FIntPoint(X + 1, Y) == Start)) {
			if (MinWave > Sel) {
				NewFinish = FIntPoint(X + 1, Y);
				MinWave = Sel;
			}
		}
	}
	if ( Y <= Map->RetMapSize().Y - 2) {
		int32 Sel = Map->Get(X, Y + 1);
		if (Sel != -1 && (Sel != 0 || FIntPoint(X, Y + 1) == Start)) {
			if (MinWave > Sel) {
				NewFinish = FIntPoint(X, Y + 1);
				MinWave = Sel;
			}
		}
	}
	if (Y >= 1) {
		int32 Sel = Map->Get(X, Y - 1);
		if (Sel != -1 && (Sel != 0 || FIntPoint(X, Y - 1) == Start)) {
			if (MinWave > Sel) {
				NewFinish = FIntPoint(X, Y - 1);
				MinWave = Sel;
			}
		}
	}
	//
	return FindWayFromMap(Map, Start, NewFinish, Way);
	//
}
