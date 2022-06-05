#include <stdio.h>
#include "math.h"
int main() {
    char first = 'i';
    char second[] = "sqrt(i)";
    char third[] = "cbrt(i)";

    printf("%7c%16s%16s\n", first,second,third);
    printf("%7s%16s%16s\n","--------","---------------","---------------");
    for (int i = 1; i <= 30; ++i) {
        printf("%7d%16.9f%16.9f\n",i, sqrt(i), cbrt(i));
    }
    printf("%7s%16s%16s\n","--------","---------------","---------------");
    return 0;
}