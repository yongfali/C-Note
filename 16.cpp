#include <iostream>
#include <string>
#include <fstream>
#include <memory> //智能指针头文件

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

	//智能指针的使用 auto_ptr(C++ 98 使用， C++11 抛弃)，unique_ptr, shared_ptr, weak_ptr 位于头文件<memory>中
	//C++ 11 使用shared_ptr代替了auto_ptr;
	//后三种智能指针是C++11才引入的

	return 0;

}