#include <stdio.h>
#include <string.h>

int main(void){
    char str[] = "Author Name";//11
    char str2[] = "----------";//10
    char str1[] = "F. Scott Fitzgerald";//19
    strupr(str1);
    printf("%d", strlen(str1));
}