/* scanf.c */

/* To link in the math.h library:
 * bash$ gcc -Wall -Werror simple.c -lm */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

int main()
{                  /*       [0]1 2 3 4  ...[31] */
                   /*       +-----------------+ */
  char name[32];   /* name: | | | | | | ... | | */
                   /*       +-----------------+ */

  /* Above, name is a pointer to the first byte of the array */


  /* note that name is uninitialized here: */
  printf( "name: %s\n", name );

  printf( "Enter your name: " );
  scanf( "%s", &name );
  printf( "Hello %s\n", name );

            /*    +----+ */
  float x;  /* x: |    | */
            /*    +----+ */
  printf( "Enter a number: " );
  scanf( "%f", &x );   /* & is the address-of operator */
  printf( "The square root of %f is %f\n", x, sqrt( x ) );

  return EXIT_SUCCESS;
}