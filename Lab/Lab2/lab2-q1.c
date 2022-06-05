/* lab2-q1.c */
/* compile in ubuntu with gcc */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
/* The 0x prefix below indicates a hexadecimal number */
int secret = 0x74616544;
int secret2 = 0x74532068;
int secret3 = 0x646E6172;
int secret4 = 0x20676E69;
char * cptr = (char *)&secret;
char * cptr2 = (char *)&secret2;
char * cptr3 = (char *)&secret3;
char * cptr4 = (char *)&secret4;
printf( "%c", *cptr++ );
printf( "%c", *cptr++ );
printf( "%c", *cptr++ );
printf( "%c", *cptr++ );

printf( "%c", *cptr2++ );
printf( "%c", *cptr2++ );
printf( "%c", *cptr2++ );
printf( "%c", *cptr2++ );

printf( "%c", *cptr3++ );
printf( "%c", *cptr3++ );
printf( "%c", *cptr3++ );
printf( "%c", *cptr3++ );

printf( "%c", *cptr4++ );
printf( "%c", *cptr4++ );
printf( "%c", *cptr4++ );
printf( "%c\n", *cptr4++ );
return EXIT_SUCCESS;

long int a = 0x20746F6E20796857;
}