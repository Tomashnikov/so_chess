#include <ncurses.h>
#include <iostream>
#include <cstdlib>
#include <mutex>
#include <vector>
#include <thread>
#include <ctime>

using namespace std;

void boardClear();

std::vector<std::vector<bool> > board;   //board matrix
std::mutex mx;                           //matrix mutex

int main()
{

    board.resize(10);
    for(int x=0; x<board.size();x++){
    board[x].resize(10);
    }

	initscr();

    auto tClear = thread(boardClear);


	endwin();
	return 0;


}
