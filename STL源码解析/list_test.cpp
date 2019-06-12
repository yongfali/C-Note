#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

int main(int argc, char const *argv[])
{
	list<int> ilist;
	cout << "size=" << ilist.size() << endl;

	cout << "--------------------------" << endl;

	ilist.push_back(0);
	ilist.push_back(1);
	ilist.push_back(2);
	ilist.push_back(3);
	ilist.push_back(4);

	cout << "size=" << ilist.size() << endl;

	cout << "--------------------------" << endl;

	list<int>::iterator ite;
	for (ite = ilist.begin(); ite != ilist.end(); ++ite)
		cout << *ite << " ";
	cout << endl;

	cout << "--------------------------" << endl;

	ite = find(ilist.begin(), ilist.end(), 3);
	if(ite != ilist.end())
		ilist.insert(ite, 99);

	cout << "size=" << ilist.size() << endl;
	cout << *ite << endl;

	cout << "--------------------------" << endl;

	for (ite = ilist.begin(); ite != ilist.end(); ++ite)
		cout << *ite << " ";
	cout << endl;

	cout << "--------------------------" << endl;

	ite = find(ilist.begin(), ilist.end(), 1);
	if(ite != ilist.end())
		cout << *(ilist.erase(ite)) << endl;

	for (ite = ilist.begin(); ite != ilist.end(); ++ite)
		cout << *ite << " ";
	cout << endl;

	return 0;
}