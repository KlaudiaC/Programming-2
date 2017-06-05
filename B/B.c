// Klaudia C - 10.04.2016

#include <stdio.h>
#include <stdlib.h>

int zmianaKierunku(char c){
	if(c == 'F') return 0;
	if(c == 'R') return 1;
	if(c == 'B') return 2;
	if(c == 'L') return 3;
	return -1;
}

char wypisanieKierunku(int d){
	if(d == 0) return '^';
	if(d == 1) return '>';
	if(d == 2) return 'v';
	if(d == 3) return '<';
	return ' ';
}

void zuczek(char *droga, int poziom, int *x, int *y, int *dir){
	char *d = droga;
	while(*d){
		*dir = (*dir + zmianaKierunku(*d)) % 4; // ilosc obrotow zuczka do uzyskania pozadanego kierunku
		*(*dir&1 ? x : y) += 1 - (*dir&2); // sprawdzenie bitow - pierwszy to wspolrzedna, drugi jest kierunkiem na osi
		printf("%c", wypisanieKierunku(*dir));
		if(poziom > 1) zuczek(droga, poziom - 1, x, y, dir);
		d++;
	}
}

int main(){
    int w; // dlugosc wzorca
    int z; // poziom zaglebienia = {1, 2, 3}
	int x = 0, y = 0, dir = 0;

    scanf("%d%d", &w, &z);
    char* trasa = (char*) malloc(w + 1); // wzorzec drogi zuczka (1 na znak konca stringa)
    scanf("%s", trasa);
    zuczek(trasa, z, &x, &y, &dir);
    printf("\n%d %d\n", x, y);

    return 0;
}
