#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char const *argv[])
{
	int n;
	int a[256];
	while(cin >> n){
		cout << "input arr" << endl;
		for(int i = 0; i < n; ++i)
			cin >> a[i];
		cout<<" output result"<< endl;
		do{
			for (int i = 0;i < n;++i){
				cout<<a[i]<<" ";
			}
			cout<<endl;
		}while (next_permutation(a, a+n));

		cout<<"------------END-------------"<<endl; 
	}
	return 0;
}