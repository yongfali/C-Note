#include<iostream>
#include<stdio.h>
#include<string>
#include<cctype>
#include<fstream>
using namespace std;  

int main()
{
/**
第二章  开始学习C++ 
**/
cout << "-----------第二章  开始学习C++------------------" << endl;	
//2.1：C++允许连续赋值 
	int a, b, c;
    a = b = c = 10;
    printf("%d\n%d\n%d\n", a,b,c);
    printf("\n");	 
    cout << a << " " << b << " "<< c << endl; 
 //2.4 function_name(void)显示的说明函数不接受任何参数，也可以省略void则表示隐式
 	int randNum = rand(); 
 	cout << "rand = " << randNum <<endl;
 	
/**
第四章 C++符合类型数据
**/
cout << "-----------第四章 C++符合类型数据------------------" << endl;
//4.1 编译器不会检查数组使用的下标是否有效，如下面的arr[100],编译会通过，但这种做法有可能会破坏程序。 
 	int arr[10] = {0};
 	cout << "the size of arr = " << sizeof(arr) << endl; 
	
/**
第五章 循环和关系表达式 
**/
cout << "-----------第五章 循环和关系表达式 ------------------" << endl;	
	//cin.get()函数的使用
	char ch;
	int count = 0;
	cout << "Enter Characters; Enter # to quit:" << endl;
	cin.get(ch);
	while(ch != '#'){
		cout << ch;
		++count;
		cin.get(ch);
	}
	cout << endl << count << " characters read" << endl;
		
   	return 0; 
}
