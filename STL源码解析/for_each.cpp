#include <iostream>
#include <algorithm>

using namespace std;

//测试仿函数用于for_each()的情形
template <typename T>
class print
{
public:
	void operator()(const T& elem){ //仿函数也称函数对象，主要是重载了运算符"()"
		cout << elem << ' ';
	}
	
};

int main(int argc, char const *argv[])
{
	int arr[6] = {1, 3, 4, 5, 6, 7};
	vector<int> vec (arr, arr + 6);
	for_each(vec.begin(), vec.end(), print<int>());
	return 0;
}
