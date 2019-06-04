#include <iostream>
#include <memory>

using namespace std;

class A;
class B;

class A{
private:
	weak_ptr<B> b;
public:
	A(){cout << "A default construct function!" << endl;}
	~A(){cout << "A default delete function!" << endl;}
	void setB(shared_ptr<B> b_ptr){
		b = b_ptr;
	}
};

class B{
private:
	weak_ptr<A> a;
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
 * [测试智能指针weak_ptr可以解决shared_ptr循环应用的问题，从而避免资源的泄漏]
 * @param  argc [description]
 * @param  argv [description]
 * @return      [description]
 */
int main(int argc, char const *argv[])
{
	test(); 
	return 0;
}