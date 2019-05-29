#include <iostream>

using namespace std;

/**
 * 第十三章类的继承
 * 
 */

class Base{
private:
	int num;

public:
	virtual void printNum(){
		cout << "Base class" << endl;
	}

	virtual ~Base(){
		cout << "Base delete" << endl;
	}
};

class Child : public Base{
private:
	int time;

public:
	void printNum(){
		cout << "Child class" << endl;
	}
	
	~Child(){
		cout << "Child delete" << endl;
	}
};

int main(){
	Base * bs = new Child;
	bs->printNum();
	delete bs;
	//cout << "test" << endl;
	return 0;
}