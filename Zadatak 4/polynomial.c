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
        if(sscanf(bufferPtr, " %d %d %n", &coefficient, &exponent, &size) == 2)
        {
            InsertExponentSorted(numberHead, coefficient, exponent);

            bufferPtr += size;  
        }
        else
        {
            printf("File isn't in the correct format\n");
            break;
        }
        
    } while (strlen(bufferPtr) > 0);

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

int AddPolynomials(Position firstNumberHead, Position secondNumberHead, Position resultHead)
{
    Position temp1 = firstNumberHead->next;
    Position temp2 = secondNumberHead->next;
    Position tempResult = resultHead;

    while (temp1 && temp2)
    {
        if (temp1->exponent == temp2->exponent)
        {
            if (temp1->coefficient+temp2->coefficient != 0)
            {
                InsertExponentSorted(resultHead, (temp1->coefficient+temp2->coefficient), temp1->exponent);
            }

            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        else if (temp1->exponent > temp2->exponent || !temp2)
        {
            InsertExponentSorted(resultHead, temp1->coefficient, temp1->exponent);

            temp1 = temp1->next;
        }
        else
        {
            InsertExponentSorted(resultHead, temp2->coefficient, temp2->exponent);

            temp2 = temp2->next;
        }
    }

    if (!temp2)
    {
        while(temp1)
        {
            InsertExponentSorted(resultHead, temp1->coefficient, temp1->exponent);

            temp1 = temp1->next;
        }
    }
    else
    {
        while(temp2)
        {
            InsertExponentSorted(resultHead, temp2->coefficient, temp2->exponent);

            temp2 = temp2->next;
        }
    }
}


int PrintNumber(Position numberHead)
{
    Position temp = numberHead->next;

    if (temp)
    {
        printf("%s", temp->coefficient >= 0 ? "" : "-");
    }
    else
    {
        printf("0");
    }

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
            printf(" %s ", temp->next->coefficient > 0 ? "+" : "-");
        }

        temp = temp->next;
    }

    printf("\n");

    return EXIT_SUCCESS;
}
