#include "Board.h"
#include "Stone.h"


bool checkGameState(const int blackStoneCount, const int whiteStoneCount, Stone* blackStone, Stone* whiteStone)
{
    const int emptySpaceCount = (MAX_BOARD_SIZE * MAX_BOARD_SIZE) - blackStoneCount - whiteStoneCount;

    if (emptySpaceCount == 0)
    {
        if (blackStoneCount > whiteStoneCount)
        {
            gotoxy(0, MAX_BOARD_SIZE + 1);
            std::cout << blackStone->GetStoneShape()<< ":" << blackStoneCount << " " << whiteStone->GetStoneShape()<< ":" << whiteStoneCount << "    흑돌의 승리!";
            return true;
        }
        if (blackStoneCount < whiteStoneCount)
        {
            gotoxy(0, MAX_BOARD_SIZE + 1);
            std::cout << blackStone->GetStoneShape() << ":" << blackStoneCount << " " << whiteStone->GetStoneShape() << ":" << whiteStoneCount << "    백돌의 승리!";
            return true;
        }
        if (blackStoneCount == whiteStoneCount)
        {
            gotoxy(0, MAX_BOARD_SIZE + 1);
            std::cout << blackStone->GetStoneShape() << ":" << blackStoneCount << " " << whiteStone->GetStoneShape() << ":" << whiteStoneCount << " 비겼습니다!";
            return true;
        }
    }

    if (blackStoneCount == 0)
    {
        gotoxy(0, MAX_BOARD_SIZE + 1);
        std::cout << blackStone->GetStoneShape() << ":" << blackStoneCount << " " << whiteStone->GetStoneShape();
        return true;
    }
    if (whiteStoneCount == 0)
    {
        gotoxy(0, MAX_BOARD_SIZE + 2);
        std::cout << blackStone->GetStoneShape() << ":" << blackStoneCount << " " << whiteStone->GetStoneShape();
        return true;
    }
    return false;
}

int main()
{
    system("mode con:cols=50 lines=20");
    HANDLE hStdin;
    DWORD fdwSaveOldMode;
    INPUT_RECORD mouseInput;
    DWORD numRead;
    Board board;
    Stone blackStone(eStoneType::BlackStone);
    Stone whiteStone(eStoneType::WhiteStone);
    Stone* currentTurn = &blackStone;
    int cursorX = 0;
    int cursorY = 0;

    hStdin = GetStdHandle(STD_INPUT_HANDLE);

    if (hStdin == INVALID_HANDLE_VALUE)
    {
        std::cout << "Error.GetStdHandle";
    }

    if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
    {
        std::cout << "Error.GetConsoleMode";
    }

    DWORD fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
    if (!SetConsoleMode(hStdin, fdwMode))
    {
        std::cout << "Error.SetConsoleMode";
    }

    board.PrintBoard();

    gotoxy(0, 10);
    std::cout << currentTurn->GetStoneShape() << " 의 차례 입니다.";

    //초기 보드에는 흑,백 각각 두개씩의 돌이 놓여있음. 
    //pair first == blackstone / second == whitestone
    std::pair<int, int> stonesCount(2, 2);
    while (!checkGameState(stonesCount.first, stonesCount.second, &blackStone, &whiteStone))
    {
        if (!ReadConsoleInput(hStdin, &mouseInput, 1, &numRead))
        {
            std::cout << "Error.ReadConsoleInput";
        }

        if (mouseInput.EventType == MOUSE_EVENT)
        {
            MOUSE_EVENT_RECORD mouse = mouseInput.Event.MouseEvent;
            switch (mouse.dwEventFlags)
            {
            case 0:
                if (mouse.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
                {
                    gotoxy(0, 10);
                    std::cout << "                                             ";
                    gotoxy(0, 10);
                    std::cout <<currentTurn->GetStoneShape() <<" 의 차례 입니다.";
                    if ((mouse.dwMousePosition.Y >= 0 && mouse.dwMousePosition.Y < MAX_BOARD_SIZE) && (mouse.dwMousePosition.X >= 0 && mouse.dwMousePosition.X < MAX_BOARD_SIZE * 2))
                    {
                        gotoxy((mouse.dwMousePosition.X / 2) * 2, mouse.dwMousePosition.Y);
                    }
                }
                break;
            case DOUBLE_CLICK:
                if ((mouse.dwMousePosition.Y >= 0 && mouse.dwMousePosition.Y < MAX_BOARD_SIZE) && (mouse.dwMousePosition.X >= 0 && mouse.dwMousePosition.X < MAX_BOARD_SIZE * 2))
                {
                    cursorX = mouse.dwMousePosition.X / 2;
                    cursorY = mouse.dwMousePosition.Y;

                    //특수문자가 2칸(2바이트)를 차지함으로서 생기는 좌표차이(클릭하는 위치와 돌이 놓이는 위치)
                    //없애기위해 /2후 출력되는 위치를 맞추기위해 *2를 함
                    gotoxy((mouse.dwMousePosition.X / 2) * 2, mouse.dwMousePosition.Y);

                    if (board.PlaceStone(cursorX, cursorY, currentTurn->GetStoneColor()))
                    {
                        board.PrintBoard();
                        stonesCount = board.GetBoardState();
                        if (currentTurn->GetStoneColor() == eStoneType::BlackStone)
                        {
                            currentTurn = &whiteStone;
                            gotoxy(0, 10);
                            std::cout << "                                             ";
                            gotoxy(0, 10);
                            std::cout << currentTurn->GetStoneShape() << " 의 차례 입니다.";
                        }
                        else
                        {
                            currentTurn = &blackStone;
                            gotoxy(0, 10);
                            std::cout << "                                             ";
                            gotoxy(0, 10);
                            std::cout << currentTurn->GetStoneShape() << " 의 차례 입니다.";
                        }
                    }
                }
                break;
            }
        }
    }

    return 0;
}