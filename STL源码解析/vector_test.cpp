#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char const *argv[])
{
	int i;
	vector<int> iv(2, 9);
	cout << "size=" << iv.size() << endl;
	cout << "capacity=" << iv.capacity() << endl;

	cout << "--------------------------" << endl;

	iv.push_back(1);
	cout << "size=" << iv.size() << endl;
	cout << "capacity=" << iv.capacity() << endl;

	cout << "--------------------------" << endl;

	iv.push_back(3);
	cout << "size=" << iv.size() << endl;
	cout << "capacity=" << iv.capacity() << endl;

	cout << "--------------------------" << endl;

	iv.push_back(4);
	cout << "size=" << iv.size() << endl;
	cout << "capacity=" << iv.capacity() << endl;

	cout << "--------------------------" << endl;

	iv.push_back(5);
	cout << "size=" << iv.size() << endl;
	cout << "capacity=" << iv.capacity() << endl;

	cout << "--------------------------" << endl;

	for(i = 0; i < iv.size(); ++i)
		cout << iv[i] << " ";
	cout << endl;

	cout << "--------------------------" << endl;

	iv.pop_back();
	iv.pop_back();
	cout << "size=" << iv.size() << endl;
	cout << "capacity=" << iv.capacity() << endl;

	cout << "--------------------------" << endl;

	vector<int>::iterator ivite = find(iv.begin(), iv.end(), 1);
	if(ivite != iv.end()) 
		iv.erase(ivite);
	cout << "size=" << iv.size() << endl;
	cout << "capacity=" << iv.capacity() << endl;

	cout << "--------------------------" << endl;

	for(int i = 0; i < iv.size(); ++i)
		cout << iv[i] << " ";
	cout << endl;

	cout << "--------------------------" << endl;

	vector<int>::iterator ivite2 = find(iv.begin(), iv.end(), 3);
	if(ivite != iv.end()) 
		iv.insert(ivite, 3, 7);
	cout << "size=" << iv.size() << endl;
	cout << "capacity=" << iv.capacity() << endl;

	cout << "--------------------------" << endl;

	for(int i = 0; i < iv.size(); ++i)
		cout << iv[i] << " ";
	cout << endl;

	cout << "--------------------------" << endl;

	iv.clear();
	cout << "size=" << iv.size() << endl;
	cout << "capacity=" << iv.capacity() << endl;

	return 0;
}