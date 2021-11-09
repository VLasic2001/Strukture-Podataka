#define MAX_SIZE (50)
#define MAX_LINE 1024

struct _Exponent;
typedef struct _Exponent* Position;
typedef struct _Exponent {
    int coefficient;
    int exponent;
    Position next;
} Exponent;

int ReadNumber(char* file, Position numberHead, int rowNumber);
int InsertExponentSorted(Position numberHead, int coefficient, int exponent);
int AddPolynomials(Position firstNumberHead, Position secondNumberHead, Position resultHead);
int PrintNumber(Position numberHead);