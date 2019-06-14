#include <iostream>
#include <functional>

using namespace std;

int main(int argc, char const *argv[])
{
	// 创建六类算数类仿函数对象
	plus<int> plusobj;
	minus<int> minusobj;
	multiplies<int> multipliesobj;
	divides<int> dividesobj;
	modulus<int> modulusobj;
	negate<int> negateobj;

	// 通过上述仿函数对象，履行函数功能
	cout << plusobj(3, 5) << endl;
	cout << minusobj(3, 5) << endl;
	cout << multipliesobj(3, 5) << endl;
	cout << dividesobj(3, 5) << endl;
	cout << modulusobj(3, 5) << endl;
	cout << negateobj(3) << endl;

	cout << "--------------------------" << endl;

	// 也可以通过临时对象来履行函数功能
	cout << plus<int>()(3, 5) << endl;
	cout << minus<int>()(3, 5) << endl;
	cout << multiplies<int>()(3, 5) << endl;
	cout << divides<int>()(3, 5) << endl;
	cout << modulus<int>()(3, 5) << endl;
	cout << negate<int>()(3) << endl;

	return 0;
}