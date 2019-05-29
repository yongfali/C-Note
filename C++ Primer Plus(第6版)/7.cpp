#include<iostream>
#include<string>

using namespace std;

/** 
	第七章 C++的编程模块
**/ 

void countDown(	int n){
	cout << "countDown..." << n << endl;
	if(n > 0)
		countDown(n-1);
	
	cout << n << ": kaboom" << endl;
} 
int main(){
	countDown(5);
	string list[5];
	
	cout << "Enter you list:" << endl;
	for(int i = 0; i < 5; ++i){
		cout << i << "+1：" << endl;
		getline(cin, list[i]); 
	} 
	
	cout << "Show you list:" << endl;
	for(int i = 0; i < 5; ++i){
		cout << list[i] << endl;
	}
	
	//递归的使用
	 
	return 0;
}