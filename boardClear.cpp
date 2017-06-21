#include <vector>
#include <mutex>
#include <thread>

using namespace std;

extern std::vector<std::vector<bool> > board;   //board matrix
extern std::mutex mx;                           //matrix mutex

void boardClear()
{
	while(true)
	{	mx.lock();
		for (int i=0; i<=board.size(); i++)
		{
			for (int j=0; j<=board[i].size(); j++)
			{
				board[i][j] = false;
			}
		}
		mx.unlock();
		this_thread::sleep_for(std::chrono::seconds(30));
	}
}
