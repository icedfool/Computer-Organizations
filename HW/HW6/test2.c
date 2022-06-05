#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void processLineData(char* lineContent){
    char * pch;
    char  **varible = calloc(1024,sizeof(char* ));
    pch = strtok (lineContent," ");
    int i = 0;
    //get all content in a line into the varible array
    while (pch != NULL){
        varible[i] = pch;
        printf("%s\n", varible[i]);
        pch = strtok (NULL, " ");
    }
}

int main(){
    char a[] = "this is a sentence";
    processLineData(a);
    return 0;
}