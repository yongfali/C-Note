#include <iostream>
#include <string>
#include <typeinfo>

using namespace std;

//模板类的使用
template <typename T>
void printType(T num){
	cout << num << " type is " << (typeid(num).name()) << endl;
}

//友元函数的使用，即对应的友元函数可以访问类的私有属性或方法
//同理友元类一样。

class A{
private:
	int age;
public:
	A(int a) : age(a){}
	friend void printAge(A * a);
	virtual ~A(){cout << "delete object" << endl;}
};

void printAge(A *a){
	cout << "friend function using " << a -> age << endl;
}

int main(int argc, char * arcv[]){
	int a = 1.0;
	string  s = "hello";
	printType(a);
	printType(s);

	cout << "-------------------" << endl;
	A * a1 = new A(10);
	printAge(a1); 

	delete a1;
	return 0;
}