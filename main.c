#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct expense {
    int id;
    char desc[50];
    float amount;
};

// TODO: transfer some functions to separate file 
int getLineCount(const char *filename)
{
    FILE* f = fopen(filename, "r");

    char buffer[256];
    int count = 0;

    while (fgets(buffer, sizeof(buffer), f) != NULL)
    {
        count++;
    }

    fclose(f);

    return count;
}

int getNextID(const char *filename)
{
    FILE* f = fopen(filename, "r");
    if (f == NULL)
    {
        return 1;
    }
    fclose(f);

    int nextid = getLineCount(filename);
    return nextid + 1;
}

void addExpense(const struct expense* expData)
{
    FILE* f = fopen("data.txt", "a+");
    fprintf(f, "%d %s %.2f\n", expData->id, expData->desc, expData->amount);
    fclose(f);
}

int main(int argc, char* argv[])
{
   switch (*argv[1])
   {
        case 'a':
            if (argc != 4)
                printf("Not enough arguments, should be: add DESCRIPTION AMOUNT\n");
            else
            {
                struct expense exp;
                exp.id = getNextID("data.txt");
                strcpy(exp.desc, argv[2]);
                exp.amount = atoi(argv[3]);
                addExpense(&exp);
            }
        default: 
            return 1;
   }

   return 1;
}