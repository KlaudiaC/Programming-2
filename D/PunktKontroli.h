// Klaudia C - 13.05.2016

#include <iostream>
#include <cmath>
using namespace std;

class PunktKontroliBeta;

class PunktKontroli{
	friend class PunktKontroliBeta;

    const string nazwa;
    const int ilosc;
    static int iloscPunktow;
    int rozmiar;
    Pomiar **pomiary;

    public:
    PunktKontroli(const string &nazwa, const int ilosc): nazwa(nazwa), ilosc(ilosc), rozmiar(0){
        pomiary = new Pomiar *[ilosc];
        iloscPunktow++;
    }

    ~PunktKontroli(){
		for(int i = 0; i < rozmiar; i++) delete pomiary[i];
		delete pomiary;
	}

    int zwrocIloscPomiarowDoWykonania() const{
        return ilosc;
    }

    Pomiar *const *pobierzPomiary(){
        return pomiary;
    }

    static int iloscPunktowKontroli(){
		return iloscPunktow;
    }

    void zarejestrujPomiar(double wartoscZmierzona, int rok, int miesiac, int dzien, int godzina, int minuta, int sekunda){
		if(rozmiar < ilosc)
			pomiary[rozmiar++] = new Pomiar(wartoscZmierzona, Pomiar::Czas(rok, miesiac, dzien, godzina, minuta, sekunda));
    }

    void komunikat() const{
        cout << nazwa << ":" << endl;
        for(int i = 0; i < rozmiar; i++) pomiary[i] -> informacja();
    }

    virtual double predykcja(PunktKontroli **pk, int k, int iloscPK){
		double w[iloscPK];
		for(int i = 0; i < iloscPK; i++) {
			int n = (rozmiar < pk[i] -> rozmiar) ? rozmiar : pk[i] -> rozmiar;
			w[i] = 0;
			for (int j = 0; j < n; j++) w[i] += fabs(pomiary[j] -> pobierzWartosc() - pk[i] -> pomiary[j] -> pobierzWartosc());
		}

		for(int i = 0; i < iloscPK; i++){
			double x = w[i];
			int j = i;
			while (j > 0 && w[j-1] > x){
				w[j] = w[j-1];
				j--;
			}
			w[j] = x;
		}
        double srednia = 0;
		for(int i = 0; i < k; i++) srednia += w[i];

        return srednia/k;
    }
};

int PunktKontroli::iloscPunktow = 0;
