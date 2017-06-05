#include <iostream>
#include "Pomiar.h"
#include "PunktKontroli.h"
#include "PunktKontroliBeta.h"
using namespace std;

int main(){
    int ile_sasiadow = 2;
    string nazwy_punktow [] = { "A", "B", "C", "D", "E", "F", "G" };
    int ile_punktow_pomiaru = 5;
    PunktKontroli** punktyKontroli = new PunktKontroli* [ ile_punktow_pomiaru ];

    punktyKontroli [ 0 ] = new PunktKontroli ( "A", 4 );
    punktyKontroli [ 0 ]->zarejestrujPomiar ( 25, 2015, 11, 9, 13, 9, 6 );
    punktyKontroli [ 0 ]->zarejestrujPomiar ( 20, 2015, 11, 9, 13, 39, 6 );
    punktyKontroli [ 0 ]->zarejestrujPomiar ( 17, 2015, 11, 9, 14, 9, 7 );
    punktyKontroli [ 0 ]->zarejestrujPomiar ( 30, 2015, 11, 9, 14, 39, 6 );

    punktyKontroli [ 1 ] = new PunktKontroli ( "B", 4 );
    punktyKontroli [ 1 ]->zarejestrujPomiar ( 21, 2015, 11, 12, 13, 9, 6 );
    punktyKontroli [ 1 ]->zarejestrujPomiar ( 19, 2015, 11, 12, 13, 39, 6 );
    punktyKontroli [ 1 ]->zarejestrujPomiar ( 26, 2015, 11, 12, 14, 9, 7 );
    punktyKontroli [ 1 ]->zarejestrujPomiar ( 31, 2015, 11, 12, 14, 39, 6 );

    punktyKontroli [ 2 ] = new PunktKontroli ( "C", 4 );
    punktyKontroli [ 2 ]->zarejestrujPomiar ( 20, 2015, 11, 13, 13, 9, 6 );
    punktyKontroli [ 2 ]->zarejestrujPomiar ( 22, 2015, 11, 13, 13, 39, 6 );
    punktyKontroli [ 2 ]->zarejestrujPomiar ( 20, 2015, 11, 13, 14, 9, 7 );
    punktyKontroli [ 2 ]->zarejestrujPomiar ( 26, 2015, 11, 13, 14, 39, 6 );

    punktyKontroli [ 3 ] = new PunktKontroli ( "D", 4 );
    punktyKontroli [ 3 ]->zarejestrujPomiar ( 23, 2015, 11, 14, 13, 9, 6 );
    punktyKontroli [ 3 ]->zarejestrujPomiar ( 22, 2015, 11, 14, 13, 39, 6 );
    punktyKontroli [ 3 ]->zarejestrujPomiar ( 17, 2015, 11, 14, 14, 9, 7 );
    punktyKontroli [ 3 ]->zarejestrujPomiar ( 28, 2015, 11, 14, 14, 39, 6 );

    punktyKontroli [ 4 ] = new PunktKontroli ( "E", 4 );
    punktyKontroli [ 4 ]->zarejestrujPomiar ( 25, 2015, 11, 16, 13, 9, 6 );
    punktyKontroli [ 4 ]->zarejestrujPomiar ( 21, 2015, 11, 16, 13, 39, 6 );
    punktyKontroli [ 4 ]->zarejestrujPomiar ( 18, 2015, 11, 16, 14, 9, 7 );
    punktyKontroli [ 4 ]->zarejestrujPomiar ( 26, 2015, 11, 16, 14, 39, 6 );

    for( int i = 0; i < ile_punktow_pomiaru; i++ )
        punktyKontroli [ i ]->komunikat ();

    PunktKontroli punktKontroli1 = PunktKontroli ( "F", 4 );
    //PunktKontroliBeta punktKontroli1 = PunktKontroliBeta ( "F", 4 );
    punktKontroli1.zarejestrujPomiar ( 23, 2016, 1, 17, 13, 9, 6 );
    punktKontroli1.zarejestrujPomiar ( 22, 2016, 1, 18, 13, 39, 6 );
    punktKontroli1.zarejestrujPomiar ( 17, 2016, 1, 19, 14, 9, 7 );
    punktKontroli1.zarejestrujPomiar ( 28, 2016, 1, 20, 14, 39, 6 );
    punktKontroli1.komunikat ();
    cout << punktKontroli1.predykcja ( punktyKontroli, ile_sasiadow, ile_punktow_pomiaru ) << endl;
    cout << punktKontroli1.iloscPunktowKontroli() << endl;
    delete [] punktyKontroli;

    return 0;
}
