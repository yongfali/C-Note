#include <iostream>

using namespace std;

int main(int argc, const char * agrv[]){
	cout << "-------引用左值--------" << endl;  
	int a = 5;  
	int &add_a(a);  

	cout << "   a  =" << a <<"    "<<"    &a = "<<&a<< endl;  
	cout << "add_a =" << add_a<<"    "<< "&add_a = " << &add_a << endl;  
	cout << "-----------------------" << endl;  

	cout << "-------引用右值--------" << endl;  
	int b = 10; 

	// int &temp = b + 1; int &temp = 2; // 该行代码是错误的因为 b + 1 (2) 为右值表达式，不能对其进行取地址(赋值）操作，因此编译会出错。
	
	int &&add_b(b + 1);  
	cout << "   b  =" << b << "    " << "    &b = " << &b << endl;  
	cout << "add_b =" << add_b << "    " << "&add_b = " << &add_b << endl;  
	add_b++;  
	cout << "add_b++ =" << add_b << "    " << "&add_b++ = " << &add_b << endl;  
	cout << "-----------------------" << endl;  
	
	return 0;
}