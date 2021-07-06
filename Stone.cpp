#include "Stone.h"


const char* Stone::GetStoneShape() const
{
	return mShape;
}

eStoneType Stone::GetStoneColor() const
{
	return mColor;
}