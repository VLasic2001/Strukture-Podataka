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
int izracunajMaksimalniOstvareniBrojBodova(student* studenti, int brojStudenata);
void ispisiStudente(student* studenti, int brojStudenata, int maksimalniBrojBodova);

int main() {
	int brojRedaka = 0;
	student* studenti = NULL;
	int maksimalniBrojBodova = 0;

	brojRedaka = ucitajBrojRedakaIzDatoteke("studenti.txt");

    if (brojRedaka == -1 || brojRedaka == 0)
    {
        return 0;
    }

	studenti = alocirajIProcitajIzDatoteke("studenti.txt", brojRedaka);

	if (studenti == NULL){
		return 0;
	}

	maksimalniBrojBodova = izracunajMaksimalniOstvareniBrojBodova(studenti, brojRedaka);

	ispisiStudente(studenti, brojRedaka, maksimalniBrojBodova);
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
		fscanf(datoteka, " %s %s %lf", studenti[brojac].ime, studenti[brojac].prezime, &studenti[brojac].bodovi);
		brojac++;
	}

	fclose(datoteka);

	return studenti;
}

int izracunajMaksimalniOstvareniBrojBodova(student* studenti, int brojStudenata){
	int maksimalniBrojBodova = 0;
	int i = 0;

	for (i = 0; i < brojStudenata; i++){
		if (studenti[i].bodovi > maksimalniBrojBodova){
			maksimalniBrojBodova = studenti[i].bodovi;
		}
	}

	return maksimalniBrojBodova;
}

void ispisiStudente(student* studenti, int brojStudenata, int maksimalniBrojBodova){
	int i = 0;

	printf("IME\t PREZIME\t APS. BROJ BODOVA\t REL. BROJ BODOVA\n");


	for (i = 0; i < brojStudenata; i++){
		printf("%s\t %s\t\t %lf\t\t %lf\n", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi, (double)studenti[i].bodovi/(double)maksimalniBrojBodova*100);
	}

}
