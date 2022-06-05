#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
int* TwoPowArray(){
    int* returnArray = calloc(20,sizeof(int));
    for (int i = 0; i <= 10; ++i) {
        returnArray[i] = pow(2,i);
    }
    return returnArray;
}

int main (){
 int *array = TwoPowArray();
 for (int i = 10; i >= 0; --i) {
     printf("%d\n",array[i]);
 }
}