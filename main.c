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
    //TODO I think this could be faulty, investigate this later.
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

void sumExpenses()
{
    FILE* f = fopen("data.txt", "r");

    if (f == NULL)
    {
        printf("Could not read file. Exiting\n");
        exit(0);
    }

    float sum = 0.0;
    float x;

    // asterisk omits id and description
    // TODO round the number to 2 decimal points.
    while(fscanf(f, "%*d %*s %f", &x) == 1)
    {
        sum += x;
    }

    printf("Total sum of expenses is: \n");
    printf("%f\n", sum);
    
}

void listExpense()
{
    FILE* f = fopen("data.txt", "r");

    if (f == NULL)
    {
        printf("Could not read file. Exiting\n");
        exit(0);
    }

    int id;
    char desc[50];
    float amount;

    printf("Current expenses are: \n");
    while(fscanf(f, "%d %s %f", &id, desc, &amount) == 3)
    {
        printf("ID: %d Description: %s amount: %.2f\n", id, desc, amount);
    }

    fclose(f);
}

void addExpense(const struct expense* expData)
{
    FILE* f = fopen("data.txt", "a+");
    fprintf(f, "%d %s %.2f\n", expData->id, expData->desc, expData->amount);
    fclose(f);
}

int main(int argc, char* argv[]) 
{

    // TODO: change these from chars to string comparison 
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
            break;
        case 'l':
            listExpense();
            break;
        case 's':
            sumExpenses();
            break;
        default: 
            printf("Argument not supported.\n");
   }

   return 1;
}