#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cmath>

using namespace std;

int main(int argc, char const *argv[])
{
	// char suffix[11] = {'9','3','1','-','3','*','+','2','2','/','+'};
	string suffix;
	while(getline(cin, suffix)){
		stack<double> temp;

		int i = 0;
		double firstNum;
		double secondNum;
		double result;

		while(suffix[i] != '\0'){
			if(suffix[i] == ' '){
				i++;
				continue;
			}
			if(isdigit(suffix[i++])){
				// string str = suffix.substr(start, i - start + 1);
				// double tempstr = stod(str);
				// cout << tempstr << endl;
				suffix[i] = suffix[i] - '0'; //只能判定单个数字
				temp.push(suffix[i]);
				// temp.push(tempstr);
			}
			else if(suffix[i] == '+' || suffix[i] == '-' || suffix[i] == '*' || suffix[i] == '/'){
				secondNum = temp.top();
				temp.pop();
				firstNum = temp.top();
				temp.pop();

				switch(suffix[i]){
					case '+':
						result = firstNum + secondNum;
						temp.push(result);
						break;
					case '-':
						result = firstNum - secondNum;
						temp.push(result);
						break;
					case '*':
						result = firstNum * secondNum;
						temp.push(result);
						break;
					default:
						result = firstNum / secondNum;
						temp.push(result);
				}
				// cout << temp.top() << endl;
			}
			i++;
		}

		cout << "result=" << temp.top() << endl;
	}

	return 0;
}