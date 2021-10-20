//#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 128
#define MAX_LINE 1024

typedef struct {
	char ime[MAX_SIZE];
	char prezime[MAX_SIZE];
	double bodovi;
} student;

int ucitajBrojRedakaIzDatoteke(char* imeDatoteke);
student* alocirajIProcitajIzDatoteke(char* imeDatoteke, int brojRedaka);

int main() {
	int brojRedaka = 0;
	student* studenti = NULL;

	brojRedaka = ucitajBrojRedakaIzDatoteke("studenti.txt");

    if (brojRedaka == -1)
    {
        return 0;
    }

	studenti = alocirajIProcitajIzDatoteke("studenti.txt", brojRedaka);
}

int ucitajBrojRedakaIzDatoteke(char* imeDatoteke) {
	FILE* datoteka = NULL;
	int brojac = 0;
	char buffer[MAX_LINE] = { 0 };

	datoteka = fopen(imeDatoteke, "r");

	if (!datoteka) {
		printf("Otvaranje datoteke nije uspjelo\n");
		return -1;
	}

	while (!feof(datoteka)) {
		fgets(buffer, MAX_LINE, datoteka);
		brojac++;
	}

	fclose(datoteka);

	return brojac;
}

student* alocirajIProcitajIzDatoteke(char* imeDatoteke, int brojRedaka) {
	FILE* datoteka = NULL;
	int brojac = 0;
	char buffer[MAX_LINE] = { 0 };
	student* studenti = NULL;

	studenti = (student*)malloc(sizeof(student) * brojRedaka);

	if (!studenti) {
		printf("Neuspjesna alokacija memorije\n");
		return NULL;
	}

	datoteka = fopen(imeDatoteke, "r");

	if (!datoteka) {
		printf("Otvaranje datoteke nije uspjelo\n");
		return NULL;
	}

	while (!feof(datoteka)) {
		fscanf(datoteka, " %s %s %lf", studenti[brojac].ime, studenti[brojac].prezime, studenti[brojac].bodovi);
		brojac++;
	}

	return studenti;
}

