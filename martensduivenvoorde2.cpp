/*  Christian Martens (S2983001) & Walt Duivenvoorde (S2499452)
	martensduivenvoorde2.cpp
	Het programma codeert of decodeert een input text file gegeven
	door de user.
	Bij coderen checkt het programma elk getal in de input file of
	het een lychrel getal is.
	Laatst gewerkt op 1-10-2020
*/
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

//functie voor in- en output van file
void codeer(string inputfile, string outputfile){
    char kar;
    char vorigekar = '\\';

	ifstream invoer (inputfile, ios::in);
	ofstream uitvoer (outputfile, ios::out);

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

void decodeer(string inputfile, string outputfile) {
	char pprevChar = 'x';
	char prevChar = 'x';
	char curChar;
	int amount = 0;
	ifstream invoer (inputfile, ios::in);
	ofstream uitvoer (outputfile, ios::out);

	curChar = invoer.get();
	while(!invoer.eof()) {
		if(curChar == '\\' && prevChar != '\\') {
			pprevChar = prevChar;
			prevChar = curChar;
			curChar = invoer.get();
		}
		else if ((prevChar != '\\' || (prevChar == '\\'
                                 && pprevChar == '\\'))
				&& (curChar >= '0' && curChar <= '9')) {
			amount = curChar - '0';
			curChar = invoer.get();
			while (curChar >= '0' && curChar <= '9') {
				amount *= 10;
				amount += curChar - '0';
				curChar = invoer.get();
			}
			for(int i = 0; i < amount - 1; i++) {
				uitvoer.put(prevChar);
			}
		}
		else {
			uitvoer.put(curChar);
			pprevChar = prevChar;
			prevChar = curChar;
			curChar = invoer.get();
		}
	}

	invoer.close();
	uitvoer.close();
}

void input() {
	string inputfile, outputfile;
	char choice;

	cout << "Geef uw inputfile + extensie\n";
	cin >> inputfile;
	cout << "Geef uw outputfile + extensie\n";
	cin >> outputfile;
	cout << "Wilt u coderen of decoderen? (c of d)\n";
	cin >> choice;
	cout << '\n';

	if (choice == 'c') {
		codeer(inputfile, outputfile);
	}
	else if (choice == 'd') {
		decodeer(inputfile, outputfile);
	}
	else {
		cout << "Vul een juiste letter in.\n";
	}
}

int main() {
	std::cout << "Gemaakt door Christian Martens en Walt Duivenvoorde\n"
			  << "Jaar van aankomst: 2020\n"
			  << "Studierichting: Informatica\n"
			  << "Studentnummer: S2983001 & S2499452\n"
			  << "Opdracht 2: DeCoderen\n"
			  << "De user wordt gevraagd een txt file in te voeren "
			  << "waarna deze wordt gecodeerd,\n"
			  << "Of gedecodeerd naar de users keuze.\n"
			  << "In het geval van coderen wordt er gekeken of "
			  << "getallen in de file lychrel getallen zijn\n"
			  << "Laatst bewerkt op 1-10-2020\n"
			  << "______________________________\n";
	input();
	return 0;
} //main
