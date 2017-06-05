// Klaudia C - 13.05.2016

#include <iostream>
#include <cmath>
using namespace std;

class Pomiar{
	public:
    class Czas{
        int rok, miesiac, dzien, godzina, minuta, sekunda;

        public:
        Czas(): rok(0), miesiac(0), dzien(0), godzina(0), minuta(0), sekunda(0){}

        Czas(int rok, int miesiac, int dzien, int godzina, int minuta, int sekunda):
			rok(rok), miesiac(miesiac), dzien(dzien), godzina(godzina), minuta(minuta), sekunda(sekunda){}

        void wypisz() const{
            cout << (dzien < 10? "0" : "") << dzien << "-" << (miesiac < 10? "0" : "") << miesiac << "-" << rok << " ";
            cout << (godzina < 10? "0" : "") << godzina << ":" << (minuta < 10? "0" : "") << minuta << ":" << (sekunda < 10? "0" : "") <<  sekunda << endl;
        }
    };

	private:
    double wartosc;
    const Czas czas;

    public:
    Pomiar(double w, const Czas &c): wartosc(w), czas(c){}

    void informacja() const{
        czas.wypisz();
        cout << wartosc << endl;
    }

    const Czas &dataPomiaru() const{
        return czas;
    }

    double pobierzWartosc() const{
        return wartosc;
    }
};
