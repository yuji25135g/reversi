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
    unsigned long makeLegalBoard(unsigned long player, unsigned long opponent);
    void displayLegalBoard(unsigned long legalBoard, unsigned long black, unsigned long white);
    void reverse(unsigned long put, unsigned long player, unsigned long opponent);
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

void Board::displayLegalBoard(unsigned long legalBoard, unsigned long black, unsigned long white)
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

unsigned long transfer(unsigned long put, int i)
{
    switch (i) {
        case 0: //上
            return (put << 8) & 0xffffffffffffff00;
            break;
        case 1: //右上
            return (put << 7) & 0x7f7f7f7f7f7f7f00;
            break;
        case 2: //右
            return (put >> 1) & 0x7f7f7f7f7f7f7f7f;
            break;
        case 3: //右下
            return (put >> 9) & 0x007f7f7f7f7f7f7f;
            break;
        case 4: //下
            return (put >> 8) & 0x00ffffffffffffff;
            break;
        case 5: //左下
            return (put >> 7) & 0x00fefefefefefefe;
            break;
        case 6: //左
            return (put << 1) & 0xfefefefefefefefe;
            break;
        case 7: //左上
            return (put << 9) & 0xfefefefefefefe00;
            break;
        default:
            return 0;
            break;
    }
}

unsigned long newBoard[2];

void Board::reverse(unsigned long put, unsigned long player, unsigned long opponent)
{   
    // 反転する石にビットが立つ整数
    unsigned long rev = 0;
    for (int i=0; i<8; i++)
    {   
        unsigned long rev_ = 0;
        unsigned long mask = transfer(put, i);
        while ((mask != 0) && (mask & opponent) != 0)
        {
            rev_ |= mask;
            mask = transfer(mask, i);
        } 
        if ((mask & player) != 0 )
        {
            rev |= rev_;
        }
    }
    // playerの盤面
    newBoard[0] = player ^ (put | rev);
    // opponentの盤面
    newBoard[1] = opponent ^ rev;
    // return newBoard;
}

int main()
{   
    Board board;
    board.displayBoard();
    unsigned long black = 0x0400000000000000;
    unsigned long white = 0x0200000000000000;
    board.displayLegalBoard(board.makeLegalBoard(black,white), black, white);
    board.reverse(0x0100000000000000, black, white);
    board.displayLegalBoard(board.makeLegalBoard(newBoard[0], newBoard[1]), newBoard[0], newBoard[1]);

    return 0;
}