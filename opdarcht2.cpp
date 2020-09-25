
#include <iostream>
#include <fstream>
#include <cstdlib> //voor exit
#include <string>
using namespace std;

void input(){ //functie voor de input en output van een file
        string inputfile = "invoer.txt";
        ifstream invoer;
        ofstream uitvoer;
        char kar;
        invoer.open (inputfile,ios::in); // koppel invoer aan file
        if ( ! invoer ) {
            cout << "File niet geopend" << endl;
            exit (1); // stopt het programma;
        } // if
        uitvoer.open ("uitvoer.txt",ios::out);
        kar = invoer.get ( );
        while ( ! invoer.eof ( ) ) {
            uitvoer.put (kar);
            kar = invoer.get ( );
        } // while
        invoer.close ( );
        uitvoer.close ( );
}

int main() {
input();
return 0;

}
