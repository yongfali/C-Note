#include <iostream>

using namespace std;

template <typename T>
class plus{
public:
	T operator()(const T& x, const T& y){return x + y;}
};

template <typename T>
class minus{
public:
	T operator()(const T& x, const T& y){return x - y;}
};

int main(int argc, char const *argv[])
{
	plus<int> plusObj;
	minus<int> minusObj;

	//以下使用仿函数，就像使用一般函数一样
	cout << plusObj(2, 3) << endl;
	cout << minusObj(5, 1) << endl;

	//以下使用仿函数，会先产生临时对象（第一对小括号），然后临时对象调用第二对小括号
	cout << plusObj()(2, 3) << endl;
	cout << minusObj()(5, 1) << endl;

	return 0;
}