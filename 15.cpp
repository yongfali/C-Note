#include <iostream>
#include <exception>

using namespace std;

class exp1 : public exception{
public:
	const * what() {return "exp1 error";}
};

class exp2 : public exception{
public:
	const * what() {return "exp2 error";}
};

int main(int argc, const char * arrv[]){
	try{
		return (3 / 0);
	}
	catch(exception & e){
		cout << e.what() << endl;
	}

	return 0;
}