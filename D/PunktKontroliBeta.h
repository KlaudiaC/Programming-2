// Klaudia C - 13.05.2016

#include <iostream>
#include <cmath>
using namespace std;

class PunktKontroliBeta: public PunktKontroli{
    public:
    PunktKontroliBeta(const string &nazwa, const int ilosc): PunktKontroli(nazwa, ilosc){
        iloscPunktow--;
    }

    double predykcja(PunktKontroli **pk, int k, int iloscPK){
		double w[iloscPK];
		for(int i = 0; i < iloscPK; i++){
			int n = (rozmiar < pk[i] -> rozmiar) ? rozmiar : pk[i] -> rozmiar;
			w[i] = 0;
			for(int j = 0; j < n; j++) w[i] += pow(pomiary[j] -> pobierzWartosc() - pk[i] -> pomiary[j] -> pobierzWartosc(), 2);
			w[i] = sqrt(w[i]);
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

        return floor(srednia/k);
    }
};
