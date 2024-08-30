#include <stdio.h>

FILE* readFile(const char *filename)
{
    FILE* f = fopen(filename, "r");

    if (f == NULL)
    {
        printf("Could not read file. Exiting\n");
        fclose(f);
        exit(0);
    }

    return f;
}

int getLineCount(const char *filename)
{
    FILE* f = readFile(filename);

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

int getNextID()
{
    FILE* f = fopen("data.txt", "r");

    if (f == NULL)
    {
        return 1;
    }

    fclose(f);

    int nextid = getLineCount("data.txt");
    return nextid + 1;
}