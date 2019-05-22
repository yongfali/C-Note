#include "queue.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MIN_PER_HR = 60;
const RAND_MAX = 10;

bool newcustomer(double x){return (rand() * x / RAND_MAX < 1)}

int main(){
	srand(time(0));

	cout << "Case Study: Bank of Heather Automatic Teller" << endl;
	cout << "Enter maxnum size of queue: ";
	int qs;
	cin >> qs;
	Queue line(qs);

	cout << "Enter the number of simulaton hours: ";
	int hours;
	cin >> hours;

	long cyclelimit = MIN_PER_HR * hours;

	cout << "Enter the average number of customers per hour: ";
	double perhour;
	cin >> perhour;
	double min_per_cust;
	min_per_cust = MIN_PER_HR;

	Item temp;
	long turnaways = 0;
	long customers = 0;
	long served = 0;
	long sum_line = 0;
	int wait_time = 0;
	long line_wait = 0;


	for(int cycle = 0; cycle < cyclelimit; ++cycle){
		if(newcustomer(min_per_cust)){
			if(line.isfull())
				turnaways++;
			else{
				customers++;
				temp.set(cycle);
				line.enqueue(temp);
			}
		}
		if(wait_time <= 0 && !line.isempty()){
			line.deque(temp);
			wait_time = temp.ptime();
			line_wait += cycle - temp.when();
			served++;
		}
		if(wait_time > 0){
			wait_time--;
		}
		sum_line += line.queuecount();
	}

	if(customers > 0){
		cout << "Customers accepted: " << customers << endl;
		cout << " customers served: " << served << endl;
		cout << " turnaways: " << turnaways << endl;
		cout << "average queue size:";
		cout.precision(2);
		cout.setf(ios_base::fixed, ios_base::floatfield);
		cout << (double) sum_line / cyclelimit << endl;
		cout << "average wait time: " << (double) line_wait / served << "minutes" << endl;
	}
	else
		cout << "No customers!" << endl;
	cout << "Done !" << endl;

	return 0;
}