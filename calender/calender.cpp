#include <iostream>
#include <string>
using namespace std;


const string DAYS[7] = {"Sun", "Mon", "Tue", "Wed", "Thr", "Fri", "Sat"};

string block(int n) {
	if (0 < n && n < 10) {
		return "  "+to_string(n)+" ";
	}
	if (10 <= n && n < 100) {
		return " "+to_string(n)+" ";
	}
	return "    ";
}

int main () {
	int firstDay;
	cin >> firstDay;
	int numberOfDays;
	cin >> numberOfDays;

	for (int i = 0; i < 7; i++) {
		cout << DAYS[i] << " ";
	}
	
	int pos = 1;
	int day = 0;
	while (day < numberOfDays) {
		if (pos % 7 == 1) {
			cout << endl;
		}
		if (pos >= firstDay) {
			day++;
		}
		cout << block(day);
		pos++;
	}
	cout << endl;
}