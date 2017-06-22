#include <vector>
#include <mutex>
#include <thread>
#include <cstdlib>
#include <ncurses.h>

using namespace std;

extern std::vector<std::vector<bool> > board;   //board matrix
extern std::mutex mx;                           //matrix mutex


void boardState()
{
	while(true)
	{
		clear();
		mx.lock();
	    	for (int i=0; i<=board.size(); i++)
            {
                printw(" ");
                for (int j=1; j<=board[i].size()*4+3; j++)
                {
                    if(j%4 == 0)printw("+");
                    else printw("-");
                }
                printw("\n|");
                for (int j=0; j<=board[i].size(); j++)
                {

                    if(board[i][j] == false) printw("   |");
                    if(board[i][j] == true) printw(" o |");
                }
                printw("\n");

            }
		printw(" ");
		for (int j=1; j<=board.size()*4+3; j++)
		{
			if(j%4 == 0)printw("+");
			else printw("-");
		}
		mx.unlock();
		refresh();
		this_thread::sleep_for(std::chrono::milliseconds(500));

	}


}
