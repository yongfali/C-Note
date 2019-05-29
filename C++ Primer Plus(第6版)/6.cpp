#include<iostream>
#include<fstream>
#include<cctype>

using namespace std;

/**
第六章 分支语句和逻辑运算符 
**/

int main(){

cout << "-----------第六章 分支语句和逻辑运算符  ------------------" << endl;
	//字符函数库cctype位于头文件<cctype>
	cout << "cctype 库函数的使用：" << endl; 
	cout << "6.1 cctype 库函数isalpha()使用,判断是否为字母：" << endl; 
	cout << "a is alpha:" << isalpha('a') << endl;	
	cout << "1 is number:" << isdigit('1') << endl; 
	cout << "ch is space:" << isdigit(' ') << endl;
	cout << ", 是否为标点符号:" << isdigit(',') << endl;
	cout << "The using of tolower() " << tolower('A') << endl;
	//文件输入输出基本操作<fstream>
	
	/**char automobile[50];
	int year;
	double a_price, b_price;
	ofstream outFile; //创建一个文件输出对象 
	outFile.open("file_test.txt"); //关联输出的文件 
	if(!outFile.is_open()){
		cout << "open file error" << endl;
		exit(1);
	}
	
	cout << "Enter the make and model of automobile: ";
	cin.getline(automobile, 50);
	cout << "Enter the model year: ";
	cin >> year;
	cout << "Enter the original asking price: ";
	cin >> a_price;
	b_price = 0.93 * a_price;
	
	cout << fixed;
	cout.precision(2); //该函数用于控制输出浮点数的精度 
	cout.setf(ios_base::showpoint); //格式化输出 
	cout << "make and model: " << automobile << endl;
	cout << "Year: " << year << endl;
	cout << "Was asking $: " << a_price << endl;
	cout << "Now asking $: " << b_price << endl;
	
	outFile << fixed;
	outFile.precision(2);
	outFile.setf(ios_base::showpoint); 
	outFile << "make and model: " << automobile << endl;
	outFile << "Year: " << year << endl;
	outFile << "Was asking $: " << a_price << endl;
	outFile << "Now asking $: " << b_price << endl;
	
	outFile.close();**/
	
	// 文件读取操作,用eof()\fail()判断是否读取成功 
	ifstream inFile;
	inFile.open("file_test.txt"); 
	char buffer[250];
	if(!inFile.is_open()){
		cout << "open file failed" << endl;
		exit(1);
	}
	while(!inFile.eof()){
		inFile.getline(buffer, 100);
		cout << buffer << endl;
	}

	 
	return 0;
}