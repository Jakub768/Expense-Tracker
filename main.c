#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "util.c"

struct expense {
    int id;
    char desc[50];
    float amount;
};


void deleteExpense(int id)
{
   

}

void sumExpenses()
{
    FILE* f = readFile("data.txt");

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
    FILE* f = readFile("data.txt");

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
                exp.id = getNextID();
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
        case 'd': 
            deleteExpense(*argv[2]);
            break;
        default: 
            printf("Argument not supported.\n");
   }

   return 1;
}