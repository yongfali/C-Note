#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	const int arrySize = 10;
	int arr[arrySize] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	vector<int> ivect(arr, arr + 10);
	list<int> ilist(arr, arr + 10);
	deque<int> ideque(arr, arr + 10);

	vector<int>::iterator it1 = find(ivect.begin(), ivect.end(), 4);
	if(it1 == ivect.end())
		cout << "4 not found!" << endl;
	else
		cout << "4 found!" << " " << *it1 << endl;

	list<int>::iterator it2 = find(ilist.begin(), ilist.end(), 6);
	if(it2 == ilist.end())
		cout << "6 not found!" << endl;
	else
		cout << "6 found!" << " " << *it2 << endl;

	deque<int>::iterator it3 = find(ideque.begin(), ideque.end(), 10);
	if(it3 == ideque.end())
		cout << "10 not found!" << endl;
	else
		cout << "10 found!" << " " << *it3 << endl;

	return 0;
}