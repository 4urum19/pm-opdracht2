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

void input(){ //functie voor in- en output van file
        string inputfile = "invoer.txt";
        ifstream invoer;
        ofstream uitvoer;
        char kar;
        invoer.open (inputfile,ios::in); //koppel invoer aan file
        if ( ! invoer ) {
            cout << "File niet geopend" << endl;
            return;//stopt het programma;
        } //if
        uitvoer.open ("uitvoer.txt",ios::out);
        kar = invoer.get ( );
        int karteller = 1;
        while ( ! invoer.eof ( ) ) {
            char vorigekar = kar; //bewaar het voorgaande karakter
            kar = invoer.get ( );
            if (kar == vorigekar){ //vorig en huidige karakter gelijk?
                karteller++; //hoog dan de karteller op met 1
            }
            if (kar != vorigekar){ //karakters ongelijk?
                if ((vorigekar >= 48 && vorigekar <= 57)
                    || (vorigekar == 92)){ //cijfer of \?
                    uitvoer << '\\';
                }
                if (karteller == 1){ //kwam het karakter 1 keer voor?
                    uitvoer.put (vorigekar); //laat het cijfer weg
                }
                else { //put anders:
                uitvoer.put (vorigekar); //het karakter
                uitvoer << karteller; //gevolgd door aantal keer
                }
                karteller = 1; //nieuw soort karakter? teller op 1
            }
        } //while
        invoer.close ( );
        uitvoer.close ( );
}

int main() {
	int getal, *p;
	int len = 0;
	cout << "Voer een getal in: \n";
	cin >> getal;
	lychrelNumb(p, getal, len);
	input();
	return 0;
} //main