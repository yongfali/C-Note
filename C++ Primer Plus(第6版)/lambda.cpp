#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>

using namespace std;

const long size1 = 39L;
const long size2 = 100 * size1;
const long size3 = 100 * size2;
bool f3(int x){return x % 3 == 0;}
bool f13(int x){return x % 13 == 0;}

class f_mod{
private:
	int dv;
public:
	f_mod(int d = 1) : dv(d){}
	bool operator()(int x){
		return x % dv == 0;
	}
};

int main(int argc, const char * agrv[]){
	vector<int> numbers(size1);
	srand(time(0)); //以当前的时间为随机数产生的种子，这样能防止产生相同的随机数
	generate(numbers.begin(), numbers.end(), rand); //rand根据种子产生随机数

	//使用函数指针
	cout << "Samples size = " << size1 <<endl;

	int count3 = count_if(numbers.begin(), numbers.end(), f3);
	cout << "Count of numbers divisible by 3: " << count3 << endl;
	int count13 = count_if(numbers.begin(), numbers.end(), f13);
	cout << "Count of numbers divisible by 13: " << count13 << endl;

	numbers.resize(size2);
	generate(numbers.begin(), numbers.end(), rand);
	cout << "Samples size = " << size2 << endl;

	//使用仿函数
	count3 = count_if(numbers.begin(), numbers.end(), f_mod(3));
	cout << "Count of numbers divisible by 3: " << count3 << endl;
	count13 = count_if(numbers.begin(), numbers.end(), f_mod(13));
	cout << "Count of numbers divisible by 13: " << count13 << endl;

	//使用lambda表达式
	numbers.resize(size3);
	generate(numbers.begin(), numbers.end(), rand);
	cout << "Samples size = " << size3 << endl;

	count3 = count_if(numbers.begin(), numbers.end(), [](int x){return x % 3 == 0;});
	cout << "Count of numbers divisible by 3: " << count3 << endl;
	count13 = count_if(numbers.begin(), numbers.end(), [](int x){return x % 13 == 0;});
	cout << "Count of numbers divisible by 13: " << count13 << endl;

	return 0;
}