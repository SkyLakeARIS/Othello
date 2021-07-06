#pragma once
#include <vector>
#include "lib.h"

#define MAX_BOARD_SIZE (8)

class Board
{
public:
	Board()
	{
		for (int i = 0; i < MAX_BOARD_SIZE; i++)
		{
			for (int j = 0; j < MAX_BOARD_SIZE; j++)
			{
				mBoard[i][j] = eStoneType::EmptySpace;
			}
		}

		mBoard[3][3] = eStoneType::WhiteStone;
		mBoard[4][4] = eStoneType::WhiteStone;
		mBoard[3][4] = eStoneType::BlackStone;
		mBoard[4][3] = eStoneType::BlackStone;
	}

	void PrintBoard();

	bool PlaceStone(const int x, const int y, const eStoneType color);

	std::pair<int, int> GetBoardState();

private:

	bool reverseStoneRecursive(int posX, int posY, const int x, const int y, const eStoneType color);

private:
	eStoneType mBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
};
