/*lajdlf;kasjdf;laksjdf */
#include <iostream>
#include <fstream>
#include <climits>
#include <cmath>

using namespace std;

bool palindrome(int *p, int len) {
	int locLen = len - 1;
	int numb = 0;
	int revNumb = 0;
	for (int i = 0; i < len; i++) {
		numb += *(p + i) * pow(10, locLen);
		locLen--;
	}
	for (int i = len - 1; i >= 0; i--) {
		revNumb += *(p + i) * pow(10, i);
	}
	if (numb == revNumb) {
		return true;
	}
	else
		return false;
}

int main() {
	int	locGetal, getal;
	int len = 0;
	cout << "Vul een getal in: \n";
	cin >> locGetal;
	getal = locGetal;
	while(locGetal > 0) {
		locGetal /= 10;
		len++;
	}
	int arr[len] = {};
	for (int i = len - 1; i >= 0; i--){
		arr[i] = getal % 10; 
		getal /= 10;
	}
	int *p = arr;
	if (palindrome(p, len)) {
		cout << "True\n";
	}
	else
		cout << "False\n";
	return 0;
}