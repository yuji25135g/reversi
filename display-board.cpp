#include <iostream>

void displayBoard(long black, long white)
{
    const char* board = "| |";
    std::cout << board;
}

int main()
{
    displayBoard(2,3);
    return 0;
}