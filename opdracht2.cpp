/*lajdlf;kasjdf;laksjdf */
#include <iostream>
#include <fstream>
#include <climits>
#include <cmath>

using namespace std;

void lenCalc(int getal, int & len) {
	while (getal > 0) {
		getal /= 10;
		len++;
	}
}

int * numConv(int getal, int & len, int arr[]) {
	int locGetal = getal;
	for (int i = len - 1; i >= 0; i--) {
		arr[i] = getal % 10;
		getal /= 10;
	}
	return arr;
}

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
	int getal, *p;
	int len = 0;
	cout << "Voer een getal in: \n";
	cin >> getal;
	lenCalc(getal, len);
	int arr[len] = { };
	p = numConv(getal, len, arr);
	std::cout << p << '\n';
	if (palindrome(p, len)) {
		cout << "True\n";
	}
	else
		cout << "False\n";
	return 0;
}