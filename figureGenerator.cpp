#include <queue>
#include <mutex>
#include <thread>
#include <time.h>
#include <vector>

using namespace std;
extern std::vector<std::vector<bool> > board;
extern std::mutex mx;
extern queue <int> queue1;
extern queue <int> queue2;
extern std::mutex q1;
extern std::mutex q2;

void figureGenerator()
{
	srand( time( NULL ) );
	while(true)
	{
		q1.lock();
		queue1.push(rand() % board.size() );
		q1.unlock();
		q2.lock();
		queue2.push(rand() % board[0].size() );
		q2.unlock();
		std::this_thread::sleep_for (std::chrono::milliseconds(100));
	}
}
