#include <iostream>
#include <set> // multiset
#include <algorithm>
#include <iterator> // ostream_iterator

using namespace std;

template <typename T>
struct display
{
	void operator()(const T& x){
		cout << x << " ";
	}
};
int main(int argc, char const *argv[])
{
	int arr1[6] = {1, 3, 5, 7, 9, 11};
	int arr2[7] = {1, 1, 2, 3, 5, 8, 13};

	multiset<int> s1(arr1, arr1 + 6);
	multiset<int> s2(arr2, arr2 + 7);

	cout << "multiset s1:";
	for_each(s1.begin(), s1.end(), display<int>());
	cout << endl;

	cout << "--------------------------" << endl;

	cout << "multiset s2:";
	for_each(s2.begin(), s2.end(), display<int>());
	cout << endl;
	
	cout << "--------------------------" << endl;

	multiset<int>::iterator first1 = s1.begin();
	multiset<int>::iterator last1 = s1.end();
	multiset<int>::iterator first2 = s2.begin();
	multiset<int>::iterator last2 = s2.end();

	cout << "union s1 and s2:";
	set_union(first1, last1, first2, last2, ostream_iterator<int>(cout, " "));
	cout << endl;

	//当两个集合进行相关集合操作后，其对应的迭代器指针会指向容器的末端，因此需要以下两个操作使first迭代器重新指向首端
	first1 = s1.begin(); 
	first2 = s2.begin();
		
	cout << "--------------------------" << endl;
	
	cout << "intersection s1 and s2:";
	set_intersection(first1, last1, first2, last2, ostream_iterator<int>(cout, " "));
	cout << endl;

	cout << "--------------------------" << endl;

	first1 = s1.begin();
	first2 = s2.begin();
	
	cout << "difference s1 and s2:";
	set_difference(first1, last1, first2, last2, ostream_iterator<int>(cout, " "));
	cout << endl;

	cout << "--------------------------" << endl;

	first1 = s1.begin();
	first2 = s2.begin();

	cout << "symmetric difference s1 and s2:";
	set_symmetric_difference(first1, last1, first2, last2, ostream_iterator<int>(cout, " "));
	cout << endl;

	first1 = s1.begin();
	first2 = s2.begin();


	return 0;
}