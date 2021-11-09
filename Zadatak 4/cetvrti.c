#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "polynomial.h"
#include "polynomial.c"

int main()
{
    Exponent head1 = { .next = NULL, .coefficient = 0, .exponent = 0 };
    Exponent head2 = { .next = NULL, .coefficient = 0, .exponent = 0 };
    Exponent additionResultHead = { .next = NULL, .coefficient = 0, .exponent = 0 };

    Position pNumber1 = &head1;
    Position pNumber2 = &head2;
    Position pAdditionResultNumber = &additionResultHead;

    ReadNumber("polinomi.txt", pNumber1, 1);
    ReadNumber("polinomi.txt", pNumber2, 2);

    printf("Prvi broj: ");
    PrintNumber(pNumber1);
    printf("Drugi broj: ");
    PrintNumber(pNumber2);

    AddPolynomials(pNumber1, pNumber2, pAdditionResultNumber);

    printf("Rezultat zbrajanja polinoma: ");
    PrintNumber(pAdditionResultNumber);

    return EXIT_SUCCESS;
}

