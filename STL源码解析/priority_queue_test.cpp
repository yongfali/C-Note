#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

int main(int argc, char const *argv[])
{
	{
		int arr[5] = {0, 3, 6, 2, 8};
		priority_queue<int> ipq(arr, arr + 5);
		cout << "size=" << ipq.size() << endl;

		for (int i = 0; i < ipq.size(); ++i)
		{
			cout << ipq.top() << " ";
		}
		cout << endl;

		while(!ipq.empty()){
			cout << ipq.top() << " ";
			ipq.pop();
		}
		cout << endl;
	}
	return 0;
}