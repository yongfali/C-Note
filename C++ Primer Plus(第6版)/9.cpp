#include<iostream>
using namespace std;

/**
第九,十，十一，章运算符重载 
**/

class Box{
private:
	double length;
	double width;
	double height;

public:
	Box(){}
	Box(double len, double wid, double hei){
		this->length = len;
		this->width = wid;
		this->height = hei;
	}
	
	void setLength(double len){
		this->length = len;
	}
	
	double getLength(){
		return this->length;
	}
	
	void setWidth(double wid){
		this->width = wid;
	}
	
	double getWidth(){
		return this->width;
	}
	
	void setHeigth(double hei){
		this->height = hei;
	}
	
	double getHeight(){
		return this->height;
	}
	
	double getVolume(){
		return this->length * this->width * this->height;
	} 
	
	//成员版运算符重载参数会少一个，因为其中一个操作数
	//是被隐式的传递的调用对象
	//非成员函数的申明为友元函数（friend)
	Box operator+(const Box& box){
		Box box1;
		box1.length = this->length + box.length;
		box1.width = this->width + box.width;
		box1.height = this->height + box.height;
		return box1;
	}
	
	~Box(){}
	
}; 
int main(){
	//volatile 使用，可以让变量随时可能的变化都被感受到，防止被编译器优化了而导致
	//值改变了却未读取到变化后的值。 
	Box *box1 = new Box(1.0, 2.0, 3.0);
	Box *box2 = new Box(4.0, 5.0, 6.0);
	Box box3; 
	Box box4;
	Box box5;
	
	box3.setLength(2.0);
	box3.setWidth(3.0);
	box3.setHeigth(4.0);
	
	box4.setLength(3.0);
	box4.setWidth(4.0);
	box4.setHeigth(5.0);
	 
	cout << "box1 volume:" << box1->getVolume() << endl;
	cout << "box2 volume:" << box2->getVolume() << endl;
	
	box5 = box3 + box4;
	
	cout << "box5 volume:" << box5.getVolume() << endl; 
	
	delete box2;
	delete box1;
	return 0;
}
