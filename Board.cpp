#include "Board.h"


//�������� �׸��� �Լ�
void Board::PrintBoard()
{
	for (int y = 0; y < MAX_BOARD_SIZE; y++)
	{
		for (int x = 0; x < MAX_BOARD_SIZE; x++)
		{
			gotoxy(x * 2, y);
			if (mBoard[y][x] == eStoneType::EmptySpace)
			{
				if (y == 0) // ù�� �׸���
				{
					if (x == 0)
					{
						std::cout << "��";
					}
					if (x == (MAX_BOARD_SIZE - 1))
					{
						std::cout << "��";
					}
					if (x != 0 && x != (MAX_BOARD_SIZE - 1))
					{
						std::cout << "��";
					}
				}
				else // ������ �� �׸���
				{
					if (y == (MAX_BOARD_SIZE - 1))
					{
						if (x == 0)
						{
							std::cout << "��";
						}
						if (x == (MAX_BOARD_SIZE - 1))
						{
							std::cout << "��";
						}
						if (x != 0 && x != (MAX_BOARD_SIZE - 1))
						{
							std::cout << "��";
						}
					}
					else //�߰� �� �׸���
					{
						if (x == 0)
						{
							std::cout << "��";
						}
						if (x == (MAX_BOARD_SIZE - 1))
						{
							std::cout << "��";
						}
						if (x != 0 && x != (MAX_BOARD_SIZE - 1))
						{
							std::cout << "��";
						}
					}
				}
			}
			else
			{
				if (mBoard[y][x] == eStoneType::BlackStone)
				{
					std::cout << "��";
				}
				else
				{
					std::cout << "��";
				}
			}
		}
	}
}
//���� ���� �� �ִ��� üũ�ϴ� �Լ�
bool Board::PlaceStone(int x, int y, const eStoneType color)
{

	if (mBoard[y][x] != eStoneType::EmptySpace)
	{
		gotoxy(0, 10);
		std::cout << "                                             ";
		gotoxy(0, 10);
		std::cout << "���� ���� �� ���� �� �Դϴ�!";
		return false;
	}

	std::vector<std::pair<int, eDirection>> reverseStoneList;
	int count = 0;
	bool bIsFail = true;
	if (mBoard[y][x] == eStoneType::EmptySpace)
	{
		/*
			8�������� �ڽ��� �� ���̿� �ִ� ��� ���� ������ �˻���.
			�˻��ϴ� ���������� �ش� ���� �÷��̾ ������ ������ ���� ������ ���� �����̹Ƿ�
			����ġ�� �˻� �������� �����ϰ� ����Լ��� ������.
			���� ������ �ڽ��� ���� �� ��� ���� ���� + �ڽ��� ��ġ�� ���� ��(1��)�� ī��Ʈ���� ��ȯ��.
			(�Ƿ��� �Ѱ�� ���� �ǵ��� ���ϰ����� 1��ŭ�� ���� ũ�� ���޵�.)

			��ȯ���� 2 �̻��̶��(1�� �������� ���� �ٷ� ���� �ڽ��� ���� �ִ� ����), �˻��� ������ ������ ���� �����Ƿ� �ش� ������ ������ �����ϴ�
			List�� ������.


			1 2 3
			4 0 5
			6 7 8 �̶� �Ҷ� i�� x(����), j�� y(����)��, �� ��ȣ�� �������� �˻��Ѵ�.
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

		//�ֺ��� ������ ���� ���ٴ°��� �ǹ���.
		if (bIsFail)
		{
			gotoxy(0, 10);
			std::cout << "                                             ";
			gotoxy(0, 10);
			std::cout << "�ڽ��� �� ���̿� ��� ���� �־�� �մϴ�.";
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

//���忡 ������ ���� ī��Ʈ�� ��ȯ�ϴ� �Լ�
std::pair<int, int> Board::GetBoardState()
{
	/*
		pair
		1��° �ε��� : �浹�� ����
		2��° �ε��� : �鵹�� ����
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