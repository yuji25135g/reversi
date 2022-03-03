#include <iostream>
#include <bitset>
using namespace std;

class Board{
    private:
    unsigned long black;
    unsigned long white;

    public:
    Board();
    void displayBoard();
    unsigned long getBlack(){return black;}
    unsigned long getWhite(){return white;}
    int* getEvaluateChart(){return &evaluateChart;}
    unsigned long makeLegalBoard(unsigned long player, unsigned long opponent);
    void displayLegalBoard(unsigned long legalBoard);
};
Board::Board()
{
    black=0x0000000810000000;
    white=0x0000001008000000;
}

void Board::displayBoard()
{   
    unsigned long check = 0x8000000000000000;
    int count = 0;
    const char* d[] = {"１", "２", "３", "４", "５", "６", "７", "８"};
    cout << "　ＡＢＣＤＥＦＧＨ\n";
    for (int i=0; i<=7; i++)
    {   
        cout << d[i];
        for(int j=0; j<=7; j++)
        {   
            if ((black&check)==check)
                cout <<  "⚫";
            else if ((white&check)==check)
                cout << "⚪";
            else
                cout << "・";
            count++;
            check = check >> 1;
        }
        cout << '\n';
    }
}

unsigned long Board::makeLegalBoard(unsigned long player, unsigned long opponent)
{   
    // マスク
    unsigned long horizontalMask = 0x7e7e7e7e7e7e7e7e;
    unsigned long verticalMask = 0x00FFFFFFFFFFFF00;
    unsigned long allSideMask = 0x007e7e7e7e7e7e00;
    // 空きマス
    unsigned long blank = ~(player|opponent);
    // 左側
    unsigned long maskOpponentByHorizontalMask = horizontalMask & opponent;
    unsigned long t = maskOpponentByHorizontalMask & (player << 1);
    unsigned long t0 = 0;
    while(t != t0) 
    {
        t0 = t;
        t |= t & (t << 1);
    }
    unsigned long leftLegalBoard = (t << 1) & blank;
    // 右側
    t = maskOpponentByHorizontalMask & (player >> 1);
    t0 = 0;
    while(t != t0) 
    {
        t0 = t;
        t |= t & (t >> 1);
    }
    unsigned long rightLegalBoard = (t >> 1) & blank;
    // 上側
    unsigned long maskOpponentByVerticalMask = verticalMask & opponent;
    t = maskOpponentByVerticalMask & (player << 8);
    t0 = 0;
    while(t != t0) 
    {
        t0 = t;
        t |= t & (t << 8);
    }
    unsigned long upLegalBoard = (t << 8) & blank;
    // 下側
    t = maskOpponentByVerticalMask & (player >> 8);
    t0 = 0;
    while(t != t0) 
    {
        t0 = t;
        t |= t & (t >> 8);
    }
    unsigned long downLegalBoard = (t >> 8) & blank;    
    // 右上
    unsigned long maskOpponentByAllSideMask = allSideMask & opponent;
    t = maskOpponentByAllSideMask & (player << 7);
    t0 = 0;
    while(t != t0) 
    {
        t0 = t;
        t |= t & (t << 7);
    }
    unsigned long upperRightLegalBoard = (t << 7) & blank;
    // 右下
    t = maskOpponentByAllSideMask & (player >> 9);
    t0 = 0;
    while(t != t0) 
    {
        t0 = t;
        t |= t & (t >> 9);
    }
    unsigned long bottomRightLegalBoard = (t >> 9) & blank;    
    // 左上
    t = maskOpponentByAllSideMask & (player << 9);
    t0 = 0;
    while(t != t0) 
    {
        t0 = t;
        t |= t & (t << 9);
    }
    unsigned long upperLeftLegalBoard = (t << 9) & blank;     
    // 左下
    t = maskOpponentByAllSideMask & (player >> 7);
    t0 = 0;
    while(t != t0) 
    {
        t0 = t;
        t |= t & (t >> 7);
    }
    unsigned long bottomLeftLegalBoard = (t >> 7) & blank;

    return (rightLegalBoard|leftLegalBoard|upLegalBoard|downLegalBoard|upperRightLegalBoard|bottomRightLegalBoard|upperLeftLegalBoard|bottomRightLegalBoard);
}

void Board::displayLegalBoard(unsigned long legalBoard)
{   
    unsigned long check = 0x8000000000000000;
    int count = 0;
    const char* d[] = {"１", "２", "３", "４", "５", "６", "７", "８"};
    cout << "　ＡＢＣＤＥＦＧＨ\n";
    for (int i=0; i<=7; i++)
    {   
        cout << d[i];
        for(int j=0; j<=7; j++)
        {   
            if ((black&check)==check)
                cout <<  "⚫";
            else if ((white&check)==check)
                cout << "⚪";
            else if ((legalBoard&check)==check)
                cout << "＊";
            else
                cout << "・";
            count++;
            check = check >> 1;
        }
        cout << '\n';
    }
}

int main()
{   
    Board board;
    board.displayBoard();
    board.initializeEvaluateChart();
    int* array = board.getEvaluateChart();
    cout << array[0][0];

    return 0;
}