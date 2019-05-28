#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, const char * argv[]){
	// ios中常用的一些格式化设置
	// 1：修改显示时使用的计数系统 dec hex, oct,分别表示十进制，十六进制和八进制
	cout << "1：修改显示时使用的计数系统 dec hex, oct,分别表示十进制，十六进制和八进制" << endl;
	oct(cout);
	int a = 12;
	cout << "八进制下 a=" << a << endl;
	hex(cout);
	cout << "十六进制下 a=" << a << endl;
	dec(cout);
	cout << "十进制下 a=" << a << endl;

	cout << "------------------------" << endl;

	// 2：调整字段宽度 width(int w) 使用,width(int with)只影响即将显示的下一个项目
	cout << "2：调整字段宽度 width(int w) 使用" << endl;
	cout << "#";
	cout.width(10);
	cout << 12 << "#" << 24 << "#" << endl; //受width()影响
	cout << 12 << "#" << 24 << "#" << endl; //不受width()影响

	cout << "------------------------" << endl;
	
	// 3: 设置浮点数的显示精度 precision(int num) num 表示精度的位数
	cout << "3: 设置浮点数的显示精度 precision(int num) num 表示精度的位数" << endl;
	float b = 1.23456;
	cout << "init b=" << b << endl;
	cout.precision(4);
	cout << "cout.precision(4) b=" << b << endl;

	cout << "------------------------" << endl;

	// 4：打印末尾的0和小数点 setf()函数使用,举部分例子
	cout << "4：打印末尾的0和小数点 setf()函数使用" << endl;
	float c = 2.4;
	cout << "init c=" << c << endl;
	cout.setf(ios_base::showpoint);
	cout << "cout.setf(ios_base::showpoint) c= " << c << endl;

	int d = 3;
	cout << "init d=" << d << endl;
	cout.setf(ios_base::uppercase);
	cout << "cout.setf(ios_base::uppercase) d=" << d << endl;

	cout.setf(ios_base::showpos);
	cout << "setf(ios_base::showpos) d=" << d << endl;

	cout << "------------------------" << endl;

	// 5：单字符的输入
	// cout << "5：get(char &c) 函数用于单字符的获取，包括空格" << endl;
	// char str;
	// cin.get(str);
	// cout << "str=" << str << endl;

	cout << "------------------------" << endl;

	// 6：多字符的输入getline(buff, buffNum), buff表示输入到的缓冲区（自定义大小）
	// buffNum表示一次输入到缓冲内容的多少
	cout << "6：getline(cin, buff) 的使用用于多字符的输入" << endl;
	char buff[50];
	cin.getline(buff, 20);
	cout << "buff=" << buff <<endl;

	cout << "------------------------" << endl;

	for(int i = 0; i < argc; ++i){
		cout << argv[i] << endl;
	}



	return 0;
}