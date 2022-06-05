/* lab2-q1.c */
#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>
int main()
{
/* The 0x prefix below indicates a hexadecimal number */
int secret = 0x4f414d4c;
int* iptr = &secret;
char * cptr = (char *)&secret;

printf("%i\n", *iptr);
printf("%c\n", *cptr);
printf("%i\n", secret++);
printf("%i\n", secret);


printf( "%c", *cptr++ );
printf( "%c", *cptr++ );
printf( "%c", *cptr++ );
printf( "%c\n", *cptr++ );
return EXIT_SUCCESS;
//How can variable cptr point to secret if they are different data types? What does *cptr++ do?

/*

*/
}
