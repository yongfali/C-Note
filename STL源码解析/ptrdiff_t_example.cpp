#include <iostream>
#include <cstddef>

using namespace std;

int main(int argc, char const *argv[])
{
	int *b = new int(2);
	int *c = new int(3);
	ptrdiff_t result = b -c;

	cout << "ptrdiff_t example" << endl;
	cout << b << " " << c << " " << result << endl;
	return 0;
}