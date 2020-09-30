
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


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

input();
return 0;

}
