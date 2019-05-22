#include<iostream>
#include<cstring>
#include<string>

using namespace std;

/**
 * [第十二章 类和动态内存分配]
 * @return [description]
 */

//浅拷贝例子
/**class Copy{
private:
	int num;
	char* name;

public:
	Copy(){
		name = new char(20);
		cout << "copy" << endl;
	}

	~Copy(){
		cout << "~copy: " << (int) name << endl;
		delete name;
		name = NULL;
	}
};**/

class DepthCopy{
private:
	int num;
	char* name;

public:
	DepthCopy(){
		name = new char(20);
		cout << "DepthCopy" << endl;
	}

	DepthCopy(const DepthCopy &dp){
		name = new char(20);
		memcpy(name, dp.name, strlen(dp.name));
		cout << "Depth Copy" << endl;
	}

	~DepthCopy(){
		cout << "~DepthCopy: " << endl;
		delete name;
		name = NULL;
	}


};

int main(){

	//浅拷贝使用
	//{
	//	Copy cp1;
	//	Copy cp2(cp1);
	//}

	//深拷贝
	{
		DepthCopy dp1;
		DepthCopy dp2(dp1);
	}

	system("pause");
	return 0;
}