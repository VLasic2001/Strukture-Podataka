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
    Position pAdditionResultNumber = &head2;

    ReadNumber("polinomi.txt", pNumber1, 1);
    ReadNumber("polinomi.txt", pNumber2, 2);

    PrintNumber(pNumber1);
    PrintNumber(pNumber2);

    

    return EXIT_SUCCESS;
}

