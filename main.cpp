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
            std::cout << blackStone->GetStoneShape()<< ":" << blackStoneCount << " " << whiteStone->GetStoneShape()<< ":" << whiteStoneCount << "    �浹�� �¸�!";
            return true;
        }
        if (blackStoneCount < whiteStoneCount)
        {
            gotoxy(0, MAX_BOARD_SIZE + 1);
            std::cout << blackStone->GetStoneShape() << ":" << blackStoneCount << " " << whiteStone->GetStoneShape() << ":" << whiteStoneCount << "    �鵹�� �¸�!";
            return true;
        }
        if (blackStoneCount == whiteStoneCount)
        {
            gotoxy(0, MAX_BOARD_SIZE + 1);
            std::cout << blackStone->GetStoneShape() << ":" << blackStoneCount << " " << whiteStone->GetStoneShape() << ":" << whiteStoneCount << " �����ϴ�!";
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
    std::cout << currentTurn->GetStoneShape() << " �� ���� �Դϴ�.";

    //�ʱ� ���忡�� ��,�� ���� �ΰ����� ���� ��������. 
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
                    std::cout <<currentTurn->GetStoneShape() <<" �� ���� �Դϴ�.";
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

                    //Ư�����ڰ� 2ĭ(2����Ʈ)�� ���������μ� ����� ��ǥ����(Ŭ���ϴ� ��ġ�� ���� ���̴� ��ġ)
                    //���ֱ����� /2�� ��µǴ� ��ġ�� ���߱����� *2�� ��
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
                            std::cout << currentTurn->GetStoneShape() << " �� ���� �Դϴ�.";
                        }
                        else
                        {
                            currentTurn = &blackStone;
                            gotoxy(0, 10);
                            std::cout << "                                             ";
                            gotoxy(0, 10);
                            std::cout << currentTurn->GetStoneShape() << " �� ���� �Դϴ�.";
                        }
                    }
                }
                break;
            }
        }
    }

    return 0;
}