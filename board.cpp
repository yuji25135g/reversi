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

int main()
{   
    Board board;
    board.displayBoard();
    

    return 0;
}