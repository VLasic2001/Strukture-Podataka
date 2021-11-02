#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE (50)

struct _Person;
typedef struct _Person* Position;
typedef struct _Person {
    char name[MAX_SIZE];
    char surname[MAX_SIZE];
    int birthYear;
    Position next;
} Person;

void PrintAndHandleMenu(Position p);
void InputAndSetPersonInfo(char* name, char* surname, int* birthYear);
int PrependList(Position head, char* name, char* surname, int birthYear);
int PrintList(Position first);
Position CreatePerson(char* name, char* surname, int birthYear);
int InsertAfter(Position position, Position newPerson);
Position FindLast(Position head);
int AppendList(Position head, char* name, char* surname, int birthYear);
Position FindPerson(Position first, char* surname);
int DeletePerson(Position head, char* surname);

int main(int argc, char** argv)
{
    Person head = { .next = NULL, .name = {0}, .surname = {0}, .birthYear = 0 };

    Position p = &head;

    PrintAndHandleMenu(p);

    return EXIT_SUCCESS;
}

void PrintAndHandleMenu(Position p)
{
    int choice = 0, result = 0;
    char* name = (char*)malloc(MAX_SIZE*sizeof(char));
    char* surname = (char*)malloc(MAX_SIZE*sizeof(char));
    int birthYear = 0;
    char search[MAX_SIZE] = "";
    Position searchPosition = NULL;

    do {
        printf("Input the number of the action you want to do:\n"
                "1 - Add a new person to the beginning of the list\n"
                "2 - Print the list\n"
                "3 - Add a new person to the end of the list\n"
                "4 - Find a person by surname\n"
                "5 - Delete a person by surname\n"
                "0 - End program\n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            InputAndSetPersonInfo(name, surname, &birthYear);
            result = PrependList(p, name, surname, birthYear);
            if (result == -1)
            {
                printf("Person couldn't be added");
            }
            else if (result == EXIT_SUCCESS)
            {
                printf("Successfully added a new person to the list\n");
            }
            break;

        case 2:
            PrintList(p->next);
            break;

        case 3:
            InputAndSetPersonInfo(name, surname, &birthYear);
            result = AppendList(p, name, surname, birthYear);
            if (result == -1)
            {
                printf("Person couldn't be added");
            }
            else if (result == EXIT_SUCCESS)
            {
                printf("Successfully added a new person to the list\n");
            }
            break;

        case 4:
            if (p->next == NULL)
            {
                printf("There are no people in the list\n");
                break;
            }
            scanf(" %s", search);
            searchPosition = FindPerson(p->next, search);
            printf("Searched person is %s %s, birth year: %d\n", searchPosition->name, searchPosition->surname, searchPosition->birthYear);
            break;

        case 5:
            if (p->next == NULL)
            {
                printf("There are no people in the list\n");
                break;
            }
            scanf(" %s", search);
            DeletePerson(p, search);
            break;
        case 0:
            break;
        default:
            printf("Invalid action number\n");
            break;

        }
    } while(choice != 0);

}

void InputAndSetPersonInfo(char* name, char* surname, int* birthYear)
{
    printf("Enter name: \n");
    scanf(" %s", name);
    printf("Enter surname: \n");
    scanf(" %s", surname);
    printf("Enter year of birth: \n");
    scanf(" %d", birthYear);
}

int PrependList(Position head, char* name, char* surname, int birthYear)
{
    Position newPerson = NULL;

    newPerson = CreatePerson(name, surname, birthYear);
    if (!newPerson)
    {
        return -1;
    }

    InsertAfter(head, newPerson);

    return EXIT_SUCCESS;
}

int PrintList(Position first)
{
    Position temp = first;

    if(temp == NULL)
    {
        printf("No people in the list\n");
        return 0;
    }

    while (temp)
    {
        printf("Name: %s, surname: %s, birth year: %d\n", temp->name, temp->surname, temp->birthYear);
        temp = temp->next;
    }

    return EXIT_SUCCESS;
}

Position CreatePerson(char* name, char* surname, int birthYear)
{
    Position newPerson = NULL;

    newPerson = (Position)malloc(sizeof(Person));
    if (!newPerson)
    {
        perror("Can't allocate memory!\n");
        return NULL;
    }

    strcpy(newPerson->name, name);
    strcpy(newPerson->surname, surname);
    newPerson->birthYear = birthYear;
    newPerson->next = NULL;

    return newPerson;
}

int InsertAfter(Position position, Position newPerson)
{
    newPerson->next = position->next;
    position->next = newPerson;

    return EXIT_SUCCESS;
}

Position FindLast(Position head)
{
    Position temp = head;

    while (temp->next)
    {
        temp = temp->next;
    }

    return temp;
}

int AppendList(Position head, char* name, char* surname, int birthYear)
{
    Position newPerson = NULL;
    Position last = NULL;

    newPerson = CreatePerson(name, surname, birthYear);
    if (!newPerson)
    {
        return -1;
    }

    last = FindLast(head);
    InsertAfter(last, newPerson);

    return EXIT_SUCCESS;
}

Position FindPerson(Position first, char* surname)
{
    Position temp = first;

    while (temp)
    {
        if (strcmp(temp->surname, surname) == 0)
        {
            return temp;
        }

        temp = temp->next;
    }

    return NULL;
}

int DeletePerson(Position head, char* surname)
{
    Position temp = head;
    Position positionToFree = NULL;

    while (temp->next)
    {
        if(strcmp(temp->next->surname, surname) == 0)
        {
            if(temp->next->next)
            {
                positionToFree = temp->next;
                temp->next = temp->next->next;
                free(positionToFree);
                return 1;
            }
            else
            {
                positionToFree = temp->next;
                temp->next = NULL;
                free(positionToFree);
                return 1;
            }
        }

        temp = temp->next;
    }

    return 0;
}