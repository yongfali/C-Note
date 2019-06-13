#include <iostream>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

int main(int argc, char const *argv[])
{
	map<int, string> imap;
	imap[0] = "zero";
	imap[1] = "one";
	imap[2] = "two";
	imap[3] = "three";

	pair<int, string> ipair(4, "four");
	imap.insert(ipair);

	map<int, string>::iterator ite = imap.begin();
	for(; ite != imap.end(); ++ite)
		cout << ite -> first << "=" << ite -> second << " ";
	cout << endl;

	cout << "--------------------------" << endl;

	return 0;
}