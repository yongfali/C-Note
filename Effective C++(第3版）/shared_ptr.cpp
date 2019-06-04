#include <iostream>
#include <memory>

using namespace std;

class A;
class B;

class A{
private:
	shared_ptr<B> b;
public:
	A(){cout << "A default construct function!" << endl;}
	~A(){cout << "A default delete function!" << endl;}
	void setB(shared_ptr<B> b_ptr){
		b = b_ptr;
	}
};

class B{
private:
	shared_ptr<A> a;
public:
	B(){cout << "B default construct function!" << endl;}
	~B(){cout << "B default delete function!" << endl;}
	void setA(shared_ptr<A> a_ptr){
		a = a_ptr;
	}
};

void test(){
	shared_ptr<A> a(new A());
	shared_ptr<B> b(new B());
	a->setB(b);
	b->setA(a);
}
/**
 * [测试智能指针shared_ptr循环引用]
 * @param  argc [description]
 * @param  argv [description]
 * @return      [description]
 */
int main(int argc, char const *argv[])
{
	test(); //由于存在循环引用的问题导致两者析构函数没法调用从而造成内存的泄漏
	return 0;
}