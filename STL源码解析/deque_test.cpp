#include <iostream>
#include <deque>
#include <algorithm>

using namespace std;

int main(int argc, char const *argv[])
{
	//deque<int, alloc, 32> ideq(20, 9); //构造一个含有20个元素，初值为9的一个deque，其缓冲区的大小为32
	deque<int> ideq(10, 9);
	cout << "size=" << ideq.size() << endl;

	cout << "--------------------------" << endl;

	for(int i = 0; i < ideq.size(); ++i)
		cout << ideq[i] << " ";
	cout << endl;

	cout << "--------------------------" << endl;

	//重新初始化deque
	for(int i = 0; i < ideq.size(); ++i)
		ideq[i] = i;
	cout << endl;

	ideq.push_back(1);
	ideq.push_back(2);
	ideq.push_back(3);

	for(int i = 0; i < ideq.size(); ++i)
		cout << ideq[i] << " ";
	cout << endl;
	cout << "size=" << ideq.size() << endl;

	cout << "--------------------------" << endl;

	ideq.push_front(99);

	for(int i = 0; i < ideq.size(); ++i)
		cout << ideq[i] << " ";
	cout << endl;
	cout << "size=" << ideq.size() << endl;

	cout << "--------------------------" << endl;

	deque<int>::iterator ite;
	ite = find(ideq.begin(), ideq.end(), 8);
	if(ite != ideq.end())
		cout << *ite << endl;

	return 0;
}