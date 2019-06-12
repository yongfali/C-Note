#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;

int main(int argc, char const *argv[])
{
	{
		//test heap(vector)
		int ia[9] = {0, 1, 3, 2, 4, 5, 6, 7, 8};
		vector<int> ivec(ia, ia + 9);

		make_heap(ivec.begin(), ivec.end()); //默认创建的是max-heap
		for(int i = 0; i < ivec.size(); ++i)
			cout << ivec[i] << " ";
		cout << endl;

		ivec.push_back(9);
		push_heap(ivec.begin(), ivec.end());
		for(int i = 0; i < ivec.size(); ++i)
			cout << ivec[i] << " ";
		cout << endl;

		pop_heap(ivec.begin(), ivec.end()); //将堆顶元素放入尾端，实现删除（实际仍存在）
		cout << ivec.back() << endl;
		ivec.pop_back();  //实现真正意义上堆顶元素的删除
		for(int i = 0; i < ivec.size(); ++i)
			cout << ivec[i] << " ";
		cout << endl;

		cout << "输出堆排序后的结果" << endl;
		sort_heap(ivec.begin(), ivec.end());
		for(int i = 0; i < ivec.size(); ++i)
			cout << ivec[i] << " ";
		cout << endl;

	}
	{
		//test heap(array)同上
	}
	return 0;
}