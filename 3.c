#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>

void UppercasetoLowercase(FILE *fptr)
{
    FILE *fptemp = NULL;
    int ch = 0;
    fptemp = fopen("temp.txt", "w");
    while((ch = fgetc(fptr)) != EOF){
        ch = (isupper(ch)) ? tolower(ch):toupper(ch);
        fputc(ch,fptemp);
    }
    fclose(fptr);
    fclose(fptemp);
    remove("input.txt");
    rename("temp.txt","Input1.txt");
}

int main()
{
    FILE* fp = NULL;
    fp = fopen("Input1.txt","r");
    UppercasetoLowercase(fp);
}