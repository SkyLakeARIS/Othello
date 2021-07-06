#include "Board.h"


//보드판을 그리는 함수
void Board::PrintBoard()
{
	for (int y = 0; y < MAX_BOARD_SIZE; y++)
	{
		for (int x = 0; x < MAX_BOARD_SIZE; x++)
		{
			gotoxy(x * 2, y);
			if (mBoard[y][x] == eStoneType::EmptySpace)
			{
				if (y == 0) // 첫출 그리기
				{
					if (x == 0)
					{
						std::cout << "┌";
					}
					if (x == (MAX_BOARD_SIZE - 1))
					{
						std::cout << "┐";
					}
					if (x != 0 && x != (MAX_BOARD_SIZE - 1))
					{
						std::cout << "┬";
					}
				}
				else // 마지막 줄 그리기
				{
					if (y == (MAX_BOARD_SIZE - 1))
					{
						if (x == 0)
						{
							std::cout << "└";
						}
						if (x == (MAX_BOARD_SIZE - 1))
						{
							std::cout << "┘";
						}
						if (x != 0 && x != (MAX_BOARD_SIZE - 1))
						{
							std::cout << "┴";
						}
					}
					else //중간 줄 그리기
					{
						if (x == 0)
						{
							std::cout << "├";
						}
						if (x == (MAX_BOARD_SIZE - 1))
						{
							std::cout << "┤";
						}
						if (x != 0 && x != (MAX_BOARD_SIZE - 1))
						{
							std::cout << "┼";
						}
					}
				}
			}
			else
			{
				if (mBoard[y][x] == eStoneType::BlackStone)
				{
					std::cout << "○";
				}
				else
				{
					std::cout << "●";
				}
			}
		}
	}
}
//돌을 놓을 수 있는지 체크하는 함수
bool Board::PlaceStone(int x, int y, const eStoneType color)
{

	if (mBoard[y][x] != eStoneType::EmptySpace)
	{
		gotoxy(0, 10);
		std::cout << "                                             ";
		gotoxy(0, 10);
		std::cout << "돌을 놓을 수 없는 곳 입니다!";
		return false;
	}

	std::vector<std::pair<int, eDirection>> reverseStoneList;
	int count = 0;
	bool bIsFail = true;
	if (mBoard[y][x] == eStoneType::EmptySpace)
	{
		/*
			8방향으로 자신의 돌 사이에 있는 상대 돌의 개수를 검사함.
			검사하는 시점에서는 해당 돌의 플레이어가 선택한 지점에 돌이 놓이지 않은 상태이므로
			현위치는 검사 범위에서 제외하고 재귀함수를 수행함.
			리턴 값으로 자신의 돌이 될 상대 돌의 개수 + 자신의 위치에 놓일 돌(1개)의 카운트값이 반환됨.
			(실력의 한계로 본래 의도의 리턴값보다 1만큼의 값이 크게 전달됨.)

			반환값이 2 이상이라면(1은 놓으려는 지점 바로 옆에 자신의 돌이 있는 상태), 검사한 방향은 뒤집을 돌이 있으므로 해당 개수와 방향을 저장하는
			List에 저장함.


			1 2 3
			4 0 5
			6 7 8 이라 할때 i가 x(가로), j가 y(세로)로, 각 번호의 방향으로 검사한다.
		*/
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				if (!(i == 0 && j == 0) && mBoard[y+j][x+i] != color)
				{
					if (reverseStoneRecursive(x+i, y+j, i, j, color))
					{
						mBoard[y][x] = color;
						bIsFail = false;
					}
				}
			}
		}

		//주변에 뒤집을 돌이 없다는것을 의미함.
		if (bIsFail)
		{
			gotoxy(0, 10);
			std::cout << "                                             ";
			gotoxy(0, 10);
			std::cout << "자신의 돌 사이에 상대 돌이 있어야 합니다.";
			return false;
		}

		return true;
	}
	return false;
}

bool Board::reverseStoneRecursive(int posX, int posY, const int x, const int y, const eStoneType color)
{
	if (posX < 0 || posY < 0 || posX >= MAX_BOARD_SIZE || posY >= MAX_BOARD_SIZE)
	{
		return false;
	}

	if (mBoard[posY][posX] == eStoneType::EmptySpace)
	{
		return false;
	}

	if (mBoard[posY][posX] == color)
	{
		return true;
	}

	if (reverseStoneRecursive(posX+x, posY+y, x, y, color))
	{
		mBoard[posY][posX] = color;
		return true;
	}

	return false;
}

//보드에 놓여진 돌을 카운트해 반환하는 함수
std::pair<int, int> Board::GetBoardState()
{
	/*
		pair
		1번째 인덱스 : 흑돌의 갯수
		2번째 인덱스 : 백돌의 갯수
	*/
	int blackStoneCount = 0;
	int whiteStoneCount = 0;
	for (int y = 0; y < MAX_BOARD_SIZE; y++)
	{
		for (int x = 0; x < MAX_BOARD_SIZE; x++)
		{
			if (mBoard[y][x] == eStoneType::BlackStone)
			{
				blackStoneCount++;
			}
			if (mBoard[y][x] == eStoneType::WhiteStone)
			{
				whiteStoneCount++;
			}
		}
	}

	return std::make_pair(blackStoneCount, whiteStoneCount);
}