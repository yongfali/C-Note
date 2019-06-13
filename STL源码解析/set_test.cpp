#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

int main(int argc, char const *argv[])
{
	int arr[5] = {1, 3, 4, 2, 5};
	set<int> iset(arr, arr+5);
	cout << "size=" << iset.size() << endl;
	cout << "3 count=" << iset.count(3) << endl;

	cout << "--------------------------" << endl;

	iset.insert(3);
	cout << "size=" << iset.size() << endl;
	cout << "3 count=" << iset.count(3) << endl;

	cout << "--------------------------" << endl;

	iset.insert(6);
	cout << "size=" << iset.size() << endl;
	cout << "3 count=" << iset.count(3) << endl;

	cout << "--------------------------" << endl;

	iset.erase(1);
	cout << "size=" << iset.size() << endl;
	cout << "3 count=" << iset.count(3) << endl;
	cout << "1 count=" << iset.count(1) << endl;

	cout << "--------------------------" << endl;

	for (auto i = iset.begin(); i != iset.end(); ++i)
		cout << *i << " ";
	cout << endl;

	cout << "--------------------------" << endl;
	
	set<int>::iterator ite;

	// STL 中的find算法
	ite = find(iset.begin(), iset.end(), 3);

	if(ite != iset.end())
		cout << "3 found !" << endl;

	// set集中自带的算法，一般容器自带的算法效率要高于STL提供的通用算法
	auto ite1 = iset.find(1);
	if(ite1 != iset.end())
		cout << "1 not found!" << endl;
	

	cout << "--------------------------" << endl;

	return 0;
}