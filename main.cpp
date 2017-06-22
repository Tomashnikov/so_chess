#include <ncurses.h>
#include <iostream>
#include <cstdlib>
#include <mutex>
#include <vector>
#include <thread>
#include <ctime>
#include <queue>


using namespace std;

void boardClear();
void boardState();
void figureGenerator();
void ai();
bool moveHandler(int x, int y);

const int m=10;
const int n=10;

bool board[m][n];
queue <int> queue1;
queue <int> queue2;
std::mutex q1;
std::mutex q2;

         //board matrix
std::mutex mx;              //matrix mutex

int main()
{
	initscr();
	start_color();
	init_pair(1,COLOR_BLUE,COLOR_YELLOW);
	attron(COLOR_PAIR(1));
    auto tBoardClear = thread(boardClear);
    auto tBoardState = thread(boardState);
    auto tfGenerator = thread(figureGenerator);
    auto tAI = thread(ai);

	tBoardClear.join();
	tBoardState.join();
	tfGenerator.join();
	tAI.join();

	endwin();
	return 0;


}

void boardClear()
{
	while(true)
	{	mx.lock();
		for (int i=0; i<=m; i++)
		{
			for (int j=0; j<=n; j++)
			{
				board[i][j] = false;
			}
		}
		mx.unlock();
		this_thread::sleep_for(std::chrono::seconds(30));
	}
}


void boardState()
{
	while(true)
	{
		clear();
		mx.lock();
	    	for (int i=0; i<=m; i++)
            {
                printw(" ");
                for (int j=1; j<=n*4+3; j++)
                {
                    if(j%4 == 0)printw("+");
                    else printw("-");
                }
                printw("\n|");
                for (int j=0; j<=m; j++)
                {

                    if(board[i][j] == false) printw("   |");
                    if(board[i][j] == true) printw(" o |");
                }
                printw("\n");

            }
		printw(" ");
		for (int j=1; j<=m*4+3; j++)
		{
			if(j%4 == 0)printw("+");
			else printw("-");
		}
		mx.unlock();
		refresh();
		this_thread::sleep_for(std::chrono::milliseconds(500));

	}

}


void figureGenerator()
{
	srand( time( NULL ) );
	while(true)
	{
		q1.lock();
		queue1.push(rand() % m );
		q1.unlock();
		q2.lock();
		queue2.push(rand() % n );
		q2.unlock();
		std::this_thread::sleep_for (std::chrono::milliseconds(100));
	}
}


bool moveHandler(int x, int y)
{
	int r = rand() % 3;
	if(r==0 && x > 0 && board[x-1][y] == false)
	{
		board[x][y] = false;
		board[x-1][y] = true;
		return true;
	}
	if(r==1 && y < m && board[x][y+1] == false)
	{
		board[x][y] = false;
		board[x][y+1] = true;
		return true;
	}
	if(r==2 && x < m && board[x+1][y] == false)
	{
		board[x][y] = false;
		board[x+1][y] = true;
		return true;
	}
	if(r==3 && y > 0 && board[x][y-1] == false)
	{
		board[x][y] = false;
		board[x][y-1] = true;
		return true;
	}

	return false;
}

void ai()
{

    std::this_thread::sleep_for (std::chrono::seconds(5));
	while(true)
	{
		for (int i=0; i<=m; i++)
		{
			for (int j=0; j<=n; j++)
			{

				if(board[i][j] == true)
				{
					mx.lock();
					moveHandler(i,j);
					mx.unlock();
				}
			}
		}

		int x,y;
		q1.lock();
		if(int a =queue1.back())x = queue1.back();
		q1.unlock();
		q2.lock();
		if(int a = queue2.back())y = queue2.back();
		q2.unlock();
		mx.lock();
		if(board[x][y] == true) moveHandler(x,y);
		board[x][y] = true;
		mx.unlock();
		std::this_thread::sleep_for (std::chrono::milliseconds(100));
	}
}

