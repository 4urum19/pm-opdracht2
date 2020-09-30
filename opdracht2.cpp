/*lajdlf;kasjdf;laksjdf */
#include <iostream>
#include <fstream>
#include <climits>

using namespace std;

int pow(int power, int numb) {
	int retPow = 1;
	for (int i = 0; i < numb; i++) {
		retPow *= power;
	}
	return retPow;
}

void lenCalc(int getal, int & len) {
	while (getal > 0) {
		getal /= 10;
		len++;
	} //while
} //lenCalc

int * numConv(int getal, int len, int arr[]) {
	int locGetal = getal;
	for (int i = len - 1; i >= 0; i--) {
		arr[i] = getal % 10;
		getal /= 10;
	} //for
	return arr;
} //numConv

bool palindrome(int *p, int len) {
	int locLen = len - 1;
	int numb = 0;
	int revNumb = 0;
	for (int i = 0; i < len; i++) {
		numb += *(p + i) * pow(10, locLen);
		locLen--;
	} //for
	for (int i = len - 1; i >= 0; i--) {
		revNumb += *(p + i) * pow(10, i);
	} //for
	if (numb == revNumb) {
		return true;
	} //if
	else {
		return false;
	} //else
} //palindrome

bool lychrelNumb(int *p, int getal, int len) {
	int origgetal = getal;
	int it = 0;
	lenCalc(getal, len);
	int arr[len] = { };
	p = numConv(getal, len, arr);
	while(true) {
		int revNumb = 0;
		for (int i = len - 1; i >= 0; i--) {
			revNumb += *(p + i) * pow(10, i);
		} //for
		if (palindrome(p, len)) {
			cout << origgetal << " is geen lychrelgetal\n"
				 << "Dit werd duidelijk na " << it << " iteraties\n";
			return true;
			break;
		} //if
		std::cout << getal << " + " << revNumb << " = ";
		getal += revNumb;
		std::cout << getal << '\n';
		if (getal > 0 && getal < 100000000) {
			len = 0;
			lenCalc(getal, len);
			p = numConv(getal, len, arr);
			it++;
		} //if
		else {
			break;
		} //else
	} //while
	cout << origgetal << " is een lychrelkandidaat\n"
		 << "Omdat er na " << it << " INT_MAX werd bereikt\n";
	return false;
} //lychrelNumb

int main() {
	int getal, *p;
	int len = 0;
	cout << "Voer een getal in: \n";
	cin >> getal;
	lychrelNumb(p, getal, len);
	return 0;
} //main