#pragma once
#include <iostream>
#include <Windows.h>

enum class eStoneType
{
	BlackStone = -1,
	EmptySpace,
	WhiteStone
};

enum class eDirection
{
	Up,
	Down,
	Left,
	Right,
	DiagonalUpLeft,
	DiagonalUpRight,
	DiagonalDownLeft,
	DiagonalDownRight
};

enum class eMessage
{
	TurnOfBlackStone,
	TurnOfWhiteStone,
	WinBlackStone,
	WinWhiteStone,
	WrongLocation,
	StoneIsAlreadyPlaced
};

inline void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
//메세지 출력 함수
inline void Message(eMessage message)
{
	switch (message)
	{
	case eMessage::WinBlackStone:
		gotoxy(0, 11);
		std::cout << "                                            ";
		gotoxy(0, 11);

		std::cout << "흑돌이 이겼습니다!              ";
		break;
	case eMessage::WinWhiteStone:
		gotoxy(0, 11);
		std::cout << "                                            ";
		gotoxy(0, 11);
		std::cout << "백돌이 이겼습니다!              ";
		break;
	default:
		//Assert
		break;
	}
}