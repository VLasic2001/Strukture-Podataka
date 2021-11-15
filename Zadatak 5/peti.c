#include <stdio.h>
#include "declarations.h"
#include "declarations.c"

int main()
{
    double result = 0.0;

    CalculatePostfixFromFile(&result, "a.txt");

    printf("Rezultat: %lf", result);

    return 0;
}

