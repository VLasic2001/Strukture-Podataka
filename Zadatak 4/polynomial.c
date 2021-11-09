#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int ReadNumber(char* fileName, Position numberHead, int rowNumber)
{
    FILE* file = NULL;
    int i = 1;
    char buffer[MAX_LINE] = { 0 };
    char* bufferPtr = NULL;
    int coefficient = 0;
    int exponent = 0;
    int size = 0;

    file = fopen(fileName, "r");

    if (!file)
    {
        printf("Couldn't open file!");
        return EXIT_FAILURE;
    }

    for (i = 1; i < rowNumber; i++)
    {
        fgets(buffer, MAX_LINE, file);
    }

    fgets(buffer, MAX_LINE, file);

    bufferPtr = &buffer[0];

    do
    {
        sscanf(bufferPtr, " %d %d %n", &coefficient, &exponent, &size);
       
        InsertExponentSorted(numberHead, coefficient, exponent);

        bufferPtr += size;
    } while (strlen(bufferPtr) > 0 && !feof(file));

    fclose(file);

    return EXIT_SUCCESS;
}

int InsertExponentSorted(Position numberHead, int coefficient, int exponent)
{
    Position temp = numberHead;
    Position newExponent = NULL;

    newExponent = (Position)malloc(sizeof(Exponent));

    if (!newExponent)
    {
        printf("Couldn't allocate memory!");
        return EXIT_FAILURE;
    }

    newExponent->coefficient = coefficient;
    newExponent->exponent = exponent;
    newExponent->next = NULL;

    while (temp)
    {
        if (temp->next == NULL)
        {
            temp->next = newExponent;

            return EXIT_SUCCESS;
        }

        if (temp->next->exponent < exponent)
        {
            newExponent->next = temp->next;

            temp->next = newExponent;

            return EXIT_SUCCESS;
        }

        if (temp->next->exponent == exponent)
        {
            if (temp->next->coefficient == -coefficient)
            {
                Position helper = NULL;
                helper = temp->next->next;

                free(temp->next);
                temp->next = helper;

                return EXIT_SUCCESS;
            }
            else
            {
                temp->next->coefficient += coefficient;

                return EXIT_SUCCESS;
            }
        }

        temp = temp->next;
    }
}


int PrintNumber(Position numberHead)
{
    Position temp = numberHead->next;

    while(temp)
    {
        if (temp->coefficient != 1)
        {
            printf("%d", abs(temp->coefficient));
        }

        if (temp->exponent == 1)
        {
            printf("x");
        }
        else if (temp->exponent != 0)
        {
            printf("x^(%d)", temp->exponent);
        }

        if (temp->next)
        {
            if (temp->next->coefficient > 0)
            {
                printf(" + ");
            }
            else if (temp->next->coefficient < 0)
            {
                printf(" - ");
            }
        }

        temp = temp->next;
    }

    printf("\n");

    return EXIT_SUCCESS;
}
