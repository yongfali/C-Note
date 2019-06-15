#include <iostream>
#include <vector>
#include <functional>
#include <vector>
#include <algorithm>

using namespace std;

class Shape{
public:
	virtual void dispaly() = 0;
};

class Rect : public Shape{
public:
	virtual void dispaly(){ cout << "rect" << endl;}
};

class Circle : public Shape{
public:
	virtual void dispaly(){ cout << "circle" << endl;}
};

class Square : public Shape{
public:
	virtual void dispaly(){ cout << "square" << endl;}
};

int main(int argc, char const *argv[])
{
	vector<Shape*> vec; 
	// vector<Shape&> vec; // STL 不支持引用语义，因此不能写成该形式

	vec.push_back(new Rect);
	vec.push_back(new Circle);
	vec.push_back(new Square);
	vec.push_back(new Circle);
	vec.push_back(new Rect);

	// 多态调用，父类的指针调用子类的方法
	for(int i = 0; i < vec.size(); ++i)
		vec[i] -> dispaly();

	cout << "--------------------------" << endl;

	for_each(vec.begin(), vec.end(), mem_fun(&Shape::dispaly));

	//以下两种写法均是错误形式，一定要以成员函数配接器mem_fun修饰，才能被算法for_each()接收
	// for_each(vec.begin(), vec.end(), &Shape::dispaly);
	// for_each(vec.begin(), vec.end(), Shape::dispaly);

	return 0;
}