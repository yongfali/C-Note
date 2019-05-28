#include <iostream>
#include <string>
#include <fstream>
#include <memory> //智能指针头文件
#include <vector>

using namespace std;

int main(int argc, const char * arrv[]){
	// cout << "C++11 新特性初始化String: " << endl;
	// string s = {'H', 'e', 'l', 'l', 'o'};
	// string str {'H', 'e', 'l', 'l', 'o', '2'};

	// cout << "string(initializer_list<char> il):" << s << endl;
	// cout << "string(initializer_list<char> il)2:" << str << endl;

	// // string object ,输入方式有两种s
	// cout << "-------------------------" << endl;
	// cout << "string 的 第一种输入方式 cin：";
	// string inStr;
	// //cin >> inStr;
	// //cout << endl;

	// //cout << "outPut = " << inStr << endl;

	// cout << "string 的 第二种输入方式 getline(cin, str): ";

	// getline(cin, inStr);
	// cout << endl;

	// cout << "outPut = " << inStr << endl;

	// ifstream fin;
	// fin.open("file_test.txt");
	// while(!fin.is_open()){
	// 	cerr << "Can not open the file" << endl;
	// 	exit(EXIT_FAILURE);
	// }
	// string buff;
	// int count = 0;
	// getline(fin, buff, ' ');
	// while(fin){
	// 	count++;
	// 	cout << count << ":" << buff << endl;
	// 	getline(fin, buff, ' ');
	// }

	// cout << "file read done!" << endl;
	// fin.close();
	// 
	cout << "string function size() and capacity() examples " << endl;

	string empty;
	string shortStr = "bit";
	string longStr = "I am a student now!";

	cout << "empty size: " << empty.size() << " empty capacity: " << empty.capacity() << endl;
	cout << "shortStr size: " << shortStr.size() << " shortStr capacity: " << shortStr.capacity() << endl;
	cout << "longStr size: " << longStr.size() << " longStr capacity: " << longStr.capacity() << endl;

	//智能指针的使用 auto_ptr(C++ 98 使用， C++11 抛弃)，unique_ptr（与BOOST 中的scoped_ptr 功能相似）, shared_ptr, weak_ptr 位于头文件<memory>中
	//auto_ptr的拷贝和复制默认实现容易出错，容易导致所属权的转移即不同的指针对象会指向同一块内存区域
	//而导致野指针的存在或者对统一内存区域执行两次删除操作。
	//C++ 11 使用shared_ptr代替了auto_ptr;
	//后三种智能指针是C++11才引入的
	//unique_ptr 可以防止指针所有权的转移，下面的代码p2 = p1;会编译出错。但是若是P1是一个
	//临时的指针对象则允许这样赋值，如函数内返回的局部对象，因为返回后诶接管后，会自动删除
	//该临时对象。从而就会出现空指针访问数据的情况。
	
	// unique_ptr<string> p1 (new string("auto"));
	// unique_ptr<string> p2;
	// p2 = p1;
	 
	//auto_ptr p4 = p3 虽然不会报错，但是会导致p3的所属权转移到P4而在删除指针时报错
	// auto_ptr<string> p3 (new string("auto"));
	// auto_ptr<string> p4;
	// p4 = p3;
	
	// forench 循环的使用，简化循环的代码
	int arr[] = {1, 3, 4, 5, 6, 7};
	for (int temp : arr)
	{
		cout << temp << endl;
	}

	//常用的迭代器有输入/输出/正向/双向/随机访问迭代器五种，他们的功能
	//逐层增加，这里的输入迭代器针对的是从容器读取数据的，输出针对的是
	//向容器写入数据。
	
	//容器的复制算法
	cout << "容器的复制算法copy()" << endl; 
	vector<int> copyArr(6);

	copy(arr, arr + 6, copyArr.begin()); //参数依次表示为复制的起始位置，结束位置，和第一个元素复制到新数组的位置。

	for(auto temp : copyArr){
		cout << "copy array: " << temp << endl;
	}

	//容器的常概念
	
	return 0;

}