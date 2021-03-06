#include <iostream>
#include <bitset>
using namespace std;

int evaluateChart[4][256];

void initializeEvaluateChart()
{   
    const int evaluationValueForBoardSquare[][8] = 
    {
        {30,-12,0,-1,-1,0,-12,30},
        {-12,-15,-3,-3,-3,-3,-15,-12},
        {0,-3,0,-1,-1,0,-3,0},
        {-1,-3,-1,-1,-1,-1,-3,-1}
    };
    int shift;
    for (int n=0; n<=3; n++)
    {
        for (int i=0; i<=255; i++)
        {
            shift = 0x01;
            evaluateChart[n][i] = 0;
            for (int l=0; l<8; l++)
            {   
                if ((shift & i) == shift)
                {
                    evaluateChart[n][i] += evaluationValueForBoardSquare[n][l];
                }
                shift = shift << 1;

            }
        }
    }
}

int evaluateBoard(unsigned long board)
{   
    int value = 0;
    for (int i=0; i<4; i++)
    {
        value += evaluateChart[i][(board >> (8*i)) & 0xff];
    }
    for (int i=0; i<4; i++)
    {
        value += evaluateChart[3-i][(board >> (8*(i+4))) & 0xff];
    }
    return value;
}

int main()
{
    initializeEvaluateChart();
    unsigned long board = 0x0000000000020000;
    cout << evaluateBoard(board);
    return 0;
}