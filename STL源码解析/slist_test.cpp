#include <iostream>
#include <slist>
#include <algorithm>

using namespace std;


int main(int argc, char const *argv[])
{
	slist<int> islist;
	cout << "size=" << islist.size() << endl;

	islist.push_front(1);
	islist.push_front(4);
	islist.push_front(9);
	islist.push_front(7);
	islist.push_front(2);

	for (slit<int>::iterator i = islist.begin(); i != islist.end(); ++i)
		cout << *i << " ";
	cout << endl;


	return 0;
}