/*lajdlf;kasjdf;laksjdf */
#include <iostream>
#include <climits>
#include <fstream>
#include <string>

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

int pointerToInt(int & getal, int len, int *p) {
	int locPow = len - 1;
	for (int i = 0; i < len; i++) {
		getal += *(p + i) * pow(10, locPow);
		locPow--;
	}
	return getal;
}

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
		getal += revNumb;
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

void input(){ //functie voor in- en output van file
    string inputfile, outputfile;
    char kar; 
    char vorigekar = '\\';

	cout << "Geef uw inputfile + extensie\n";
	cin >> inputfile;
	cout << "Geef uw outputfile + extensie\n";
	cin >> outputfile;
	cout << '\n';

	ifstream invoer (inputfile, std::ios::in);
	ofstream uitvoer (outputfile, std::ios::out);
    
    kar = invoer.get ( );

    while ( ! invoer.eof ( ) ) {
       	int inpArr[50] = { };
       	int karteller = 1;
       	int len = 0;
       	int getal = 0;
        while(vorigekar == kar && kar != '\n') {
           	karteller++;
           	kar = invoer.get();
           	if (vorigekar != kar) {
           		uitvoer << karteller;
           		karteller = 1;
          	}
        }
        if ((kar >= '0' && kar <= '9') || kar == '\\'){ //cijfer of \?
            if (kar == '\\') {
               	uitvoer.put('\\');
            }

            while (kar >= '0' && kar <= '9') {
               	vorigekar = kar;
               	kar = invoer.get();
               	if(vorigekar == kar) {
              		inpArr[len] = vorigekar - '0';
           			len++;
           			karteller++;
           		}
           		else if (vorigekar != kar) {
          			inpArr[len] = vorigekar - '0';
           			len++;
           			uitvoer.put('\\');
               		uitvoer.put(vorigekar);
               		if (karteller > 1) {
               			uitvoer << karteller;
               			karteller = 1;
               		}
             	}
            }
            if (len > 0) {
            	int *arrPointer = inpArr;
            	pointerToInt(getal, len, arrPointer);
            	lychrelNumb(arrPointer, getal, len);
            }
        }
        uitvoer.put(kar);
        vorigekar = kar;
        kar = invoer.get();
    } //while
    invoer.close ( );
    uitvoer.close ( );
}

int main() {
	input();
	return 0;
} //main