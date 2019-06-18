#include <iostream>   // std::cout
#include <string>     // std::string, std::stod

using namespace std;
int main ()
{
	string str_bin = "2456.33";
	double  i_bin = stod (str_bin);
	cout << i_bin << endl;
	string s=to_string(i_bin);

}