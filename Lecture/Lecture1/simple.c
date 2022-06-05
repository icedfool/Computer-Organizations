/* simple.c */

/* bash$ gcc -Wall -Werror simple.c */

/* To only see the preprocessing output:
   bash$ gcc -Wall -Werror -E simple.c */

/* To link in the math.h library:
 * bash$ gcc -Wall -Werror simple.c -lm */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define BUFFER_MAX 32

int main()
{
  printf( "Hi.\n" );
  /*          ^^
   *      one single character '\n' means newline */

  printf( "Today is %s at %s.\n", __DATE__, __TIME__ );

  printf( "BUFFER_MAX is %d\n", BUFFER_MAX );


  int i;
  for ( i = 1 ; i < BUFFER_MAX / 4 ; i++ )
  {
    printf( "%03d %f %20.15f\n", i, sqrt( i ), sqrt( i ) );
    printf( "%03d %f %-20.15f\n", i, sqrt( i ), sqrt( i ) );
    printf( "%03d %f %-20.200f\n", i, sqrt( i ), sqrt( i ) );
    printf( "%03d %f %-20.200f\n", i, sqrtf( i ), sqrtf( i ) );
  }


  /* TO DO: work with the example code below to figure out
   *         the rounding behavior for float values */
  float f = 99.012346;
  printf( "printf is %f%% fun\n", f );
  printf( "printf is %.0f%% fun\n", f );

  /* TO DO: what is the exact output of the following code? */
  float j;
  printf( "printf prints j: %f\n", j );

  return EXIT_SUCCESS;   /* return 0; */
}