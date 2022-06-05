/* lab2-q1.c */
/* compile in ubuntu with gcc */
#include <stdio.h>
#include <stdlib.h>

int main(){
/* The 0x prefix below indicates a hexadecimal number */
long int* array[4]  = {0x20746F6E20796857,0x742065676E616863,0x646C726F77206568,0x3F};
/* array[0] = 0x20746F6E20796857;
array[1] = 0x742065676E616863;
array[2] = 0x646C726F77206568;
array[3] = 0x3F; */
char * cptr = (char *)&array[0];
char * cptr2 = (char *)&array[1];
char * cptr3 = (char *)&array[2];
char * cptr4 = (char *)&array[3];
for (int i = 0; i < 8; i++){
    printf( "%c", *cptr++ );
}
for (int i = 0; i < 8; i++){
    printf( "%c", *cptr2++ );
}
for (int i = 0; i < 8; i++){
    printf( "%c", *cptr3++ );
}
for (int i = 0; i < 8; i++){
    printf( "%c", *cptr4++ );
}
printf("\n");
return EXIT_SUCCESS;
}