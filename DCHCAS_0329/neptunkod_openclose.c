#include <stdio.h>
#include <stdlib.h>
#define M 200
int main()
{
    FILE *fp;
    char str[M];
    char* filename="C:\\Users\\User\\Desktop\\DCHCAS_0329\\neptunkod.txt";
    fp=fopen(filename, "r");
    if(fp==NULL){
        printf("Nem tudom megnyitni");
        return 1;
    }
    while(fgets(str,M,fp)!=NULL){
        printf("%s",str);
    }
    fclose(fp);
    return 0;
}
