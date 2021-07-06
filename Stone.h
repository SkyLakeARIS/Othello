#pragma once
#include "lib.h"

class Stone
{
public:
	Stone(eStoneType color)
	{
		if (color == eStoneType::BlackStone)
		{
			mShape = "¡Û";
			mColor = eStoneType::BlackStone;
		}
		else
		{
			mShape = "¡Ü";
			mColor = eStoneType::WhiteStone;
		}
	}

	const char* GetStoneShape() const;

	eStoneType GetStoneColor() const;

private:
	const char* mShape;
	eStoneType mColor;
};