#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_SIZE  32
void UppercasetoLowercase(FILE *fptr)
{
    FILE *fpTmp = NULL;
    int ch = 0;
    fpTmp = fopen("temp.txt", "w");
    while ( (ch = fgetc(fptr)) != EOF)
    {
        ch = (isupper(ch))? tolower(ch):toupper(ch);
        fputc(ch, fpTmp);
    }
    fclose(fptr);
    fclose(fpTmp);
    remove("input.txt");
    rename("temp.txt", "input.txt");
}
int main()
{
    FILE *fp = NULL;
    fp = fopen("input.txt", "r");
    UppercasetoLowercase(fp);
    return 0;
}