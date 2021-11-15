struct _stackElement;
typedef struct _stackElement *Position;
typedef struct _stackElement
{
    double number;
    Position next;
} StackElement;

Position CreateElement(double number);
int InsertAfter(Position position, Position newElement);
int Push(Position head, double number);
int DeleteAfter(Position position);
int Pop(double *result, Position head);
int PerformOperation(Position head, char operation);
int CalculatePostfixFromFile(double *result, char *fileName);