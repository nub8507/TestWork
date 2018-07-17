#include "TwoDimensionalArray.h"

UTwoDimensionalArray::UTwoDimensionalArray()
{
	this->Array.Empty();
	//
	this->SizeX = 0;
	this->SizeY = 0;
}

void UTwoDimensionalArray::InitArray(int32 x,int32 y)
{
	this->Array.Empty();
	for (int i = 0; i < x*y; i++)
	{
		this->Array.Add(0);
	}
	//
	this->SizeX = x;
	this->SizeY = y;
}

FIntPoint UTwoDimensionalArray::RetMapSize()
{
	return FIntPoint(this->SizeX,this->SizeY);
}

bool UTwoDimensionalArray::IsEmpty()
{
	if (this->SizeX == 0 || this->SizeY == 0)
		return true;
	return false;
}

UTwoDimensionalArray::~UTwoDimensionalArray()
{
	Array.Empty();
}

FIntPoint UTwoDimensionalArray::Num()
{
	return FIntPoint(this->SizeX,this->SizeY);
}

bool UTwoDimensionalArray::Set(int32 x, int32 y, int32 Val)
{
	//
	if (x > SizeX || y > SizeY)
		return false;
	//
	int32 ArrayPos = x * SizeY + y;
	Array[ArrayPos] = Val;
	return true;
	//
}

int32 UTwoDimensionalArray::Get(int32 x, int32 y)
{
	//
	if (x > SizeX || y > SizeY)
		return int32(-2);
	//
	int32 ArrayPos = x * SizeY + y;
	return Array[ArrayPos];
}
