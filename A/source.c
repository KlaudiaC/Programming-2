// Klaudia C - 26.03.2016

#include <stdio.h>
#include <stdlib.h>

typedef struct Point Point;
struct Point{
	int x, y, z;
	int dx, dy, dz;
	Point *next;
};

int main(){
    int l; // liczba zestawow

    scanf("%d", &l);
    while(l--){
        int X, Y, Z; // wymiary prostopadloscianu
        int x0, y0, z0; // wspolrzedne punktu startowego
        int dx, dy, dz; // wektor predkosci
        int k; // liczba krokow
        int inter; // interwal
        scanf("%d%d%d", &X, &Y, &Z);
        scanf("%d%d%d", &x0, &y0, &z0);
        scanf("%d%d%d", &dx, &dy, &dz);
        scanf("%d", &k);
        scanf("%d", &inter);
        char* points = (char*) malloc(X + Y + Z + 3 + 1);
        scanf("%s", points);

        Point *head = NULL;
        Point **tail = &head; // wskaznik na wskaznik wskazujacy na NULL
        int i = 0;
        while(i != k){
			if(i%inter == 0){
				Point *point = (Point*) malloc(sizeof(Point));
				point -> x = x0;
				point -> y = y0;
				point -> z = z0;
				point -> dx = dx;
				point -> dy = dy;
				point -> dz = dz;
				point -> next = NULL;
				*tail = point; // wskazanie na aktualny NULLowy wskaznik
				tail = &(point -> next);
			}

			Point *point = head;
			while(point){
				int odbicie = 0;

				if(point -> x + point -> dx > X || point -> x + point -> dx < 0){ // sprawdzenie, czy nie zajdzie odbicie
					point -> dx = -point -> dx;
					odbicie = 1;
				}
				if(point -> y + point -> dy > Y || point -> y + point -> dy < 0){
					point -> dy = -point -> dy;
					odbicie = 1;
				}
				if(point -> z + point -> dz > Z || point -> z + point -> dz < 0){
					point -> dz = -point -> dz;
					odbicie = 1;
				}
				if(odbicie == 1) printf("#%d:%c%c%c", i, *(points + point -> x), *(points + point -> y + X + 1), *(points + point -> z + X + Y + 2));

				point -> x += point -> dx; // przesuniecie punktu
				point -> y += point -> dy;
				point -> z += point -> dz;

				point = point -> next;
			}
            i++;
        }

        while(head){
			Point *temp = head -> next;
			free(head);
			head = temp;
		}
        free(points);
    }
    return 0;
}
