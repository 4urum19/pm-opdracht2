/*  Christian Martens (S2983001) & Walt Duivenvoorde (S2499452)
	martensduivenvoorde2.cpp
	Het programma codeert of decodeert een input text file gegeven
	door de user.
	Bij coderen checkt het programma elk getal in de input file of
	het een lychrel getal is.
	Laatst gewerkt op 2-10-2020
*/
#include <iostream>
#include <climits>
#include <fstream>
#include <string>

using namespace std;

//Power functie om machten uit te rekeken
int pow(int base, int exp) {
	int result = 1;
	for (int i = 0; i < exp; i++) {
		result *= base;
	} //for
	return result;
} //pow

//Lencalc functie om de lengte van een getal uit te rekenen
void lenCalc(int getal, int & len) {
	while (getal > 0) {
		getal /= 10;
		len++;
	} //while
} //lenCalc

//Pointer functie om van een int naar een array te converten
int * intToPointer(int getal, int len) {
	int arr[len] = { };
	for (int i = len - 1; i >= 0; i--) {
		arr[i] = getal % 10;
		getal /= 10;
	} //for
	int *returnPointer = arr;
	return returnPointer;
} //intToPointer

//Functie wat een pointer naar een integer te converten
int pointerToInt(int len, int *p) {
	int getal = 0;
	int locExp = len - 1; //Local Exponent
	for (int i = 0; i < len; i++) {
		getal += *(p + i) * pow(10, locExp);
		locExp--;
	} //for
	return getal;
} //pointerToInt

//Functie wat checkt of een array-pointer een palindroom is
bool palindrome(int *p, int len) {
	int locLen = len - 1; //Local Length
	int numb = 0; //Number
	int revNumb = 0; //Reverse Number
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

//Bool functie wat checkt of een pointer input een lychrelgetal is
bool lychrelNumb(int *arrPointer, int len) {
	int getal = pointerToInt(len, arrPointer);
	int origgetal = getal;
	int it = 0;
	while(true) {
		int revNumb = 0;
		for (int i = len - 1; i >= 0; i--) {
			revNumb += *(arrPointer + i) * pow(10, i);
		} //for
		if (palindrome(arrPointer, len)) {
			cout << origgetal << " is geen lychrelgetal\n"
				 << "Dit werd duidelijk na " << it << " iteraties\n\n";
			return true;
			break;
		} //if
		getal += revNumb;
		if (getal > 0 && getal < 100000000) {
			len = 0;
			lenCalc(getal, len);
			arrPointer = intToPointer(getal, len);
			it++;
		} //if
		else {
			break;
		} //else
	} //while
	cout << origgetal << " is een lychrelkandidaat\n"
		 << "Omdat er na " << it << " iteraties, INT_MAX werd bereikt\n\n";
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
        while(vorigekar == kar && kar != '\n') {
           	karteller++;
           	kar = invoer.get();
           	if (vorigekar != kar) {
           		uitvoer << karteller;
           		karteller = 1;
          	} //if
        } //while
        if ((kar >= '0' && kar <= '9') || kar == '\\'){ //cijfer of \?
            if (kar == '\\') {
               	uitvoer.put('\\');
            } //if

            while (kar >= '0' && kar <= '9') {
               	vorigekar = kar;
               	kar = invoer.get(); 
               	karteller = 1;
               	while (vorigekar == kar) {
              		inpArr[len] = vorigekar - '0';
           			len++;
           			karteller++;
           			kar = invoer.get();
           		} //while
           		if (vorigekar != kar) {
          			inpArr[len] = vorigekar - '0';
           			len++;
           			uitvoer.put('\\');
               		uitvoer.put(vorigekar);
               		if (karteller > 1) {
               			uitvoer << karteller;
               			karteller = 1;
               		} //if
               		else if (karteller = 1 && kar == '\\') {
               			uitvoer.put('\\');
               			karteller = 1;
               		} //elif
             	} //if
            } //while
            if (len > 0) {
            	int *arrPointer = inpArr;
            	lychrelNumb(arrPointer, len);
            } //if
        } //if
        uitvoer.put(kar);
        vorigekar = kar;
        kar = invoer.get();
    } //while
    invoer.close ( );
    uitvoer.close ( );
} //codeer

//Decodeer functie wat een gecodeerde input-file decodeert
void decodeer(string inputfile, string outputfile) {
	char pprevChar = '\b';
	char prevChar = '\b';
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
		} //if
		else if (curChar == '\\' && prevChar == '\\' && pprevChar == '\\') {
			curChar = invoer.get();
			uitvoer.put(curChar);
			pprevChar = prevChar;
			prevChar = curChar;
			curChar = invoer.get();
		} //elif
		else if ((prevChar == '\\' && pprevChar == '\\') && (curChar >= '0' && curChar <= '9')) {
			amount = curChar - '0';
			curChar = invoer.get();
			while (curChar >= '0' && curChar <= '9') {
				amount *= 10;
				amount += curChar - '0';
				curChar = invoer.get();
			} //while
			for(int i = 0; i < amount - 1; i++) {
				uitvoer.put(prevChar);
			} //for			
		} //elif
		
		else if (prevChar != '\\' && (curChar >= '0' && curChar <= '9')) {
			amount = curChar - '0';
			curChar = invoer.get();
			while (curChar >= '0' && curChar <= '9') {
				amount *= 10;
				amount += curChar - '0';
				curChar = invoer.get();
			} //while
			if (prevChar == '\\' && pprevChar != '\\') {
				uitvoer.put(curChar);
			} //if
			for(int i = 0; i < amount - 1; i++) {
				uitvoer.put(prevChar);
			} //for
		} //elif
		else {
			uitvoer.put(curChar);
			pprevChar = prevChar;
			prevChar = curChar;
			curChar = invoer.get();
		} //else
	} //while

	invoer.close();
	uitvoer.close();
} //decodeer

//input-functie wat de user vraagt naar een input, output en keuze
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
	} //if
	else if (choice == 'd') {
		decodeer(inputfile, outputfile);
	} //elif
	else {
		cout << "Vul een juiste letter in.\n";
	} //else
} //input

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
			  << "Laatst bewerkt op 2-10-2020\n"
			  << "______________________________\n";
	input();
	return 0;
} //main
