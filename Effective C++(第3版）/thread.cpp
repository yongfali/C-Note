#include <iostream>
#include <thread>

using namespace std;

void thread_task(){
	cout << "hello thread" << endl;
}

int main()
{
	std::thread t(thread_task);
	t.join();
	return 0;
}