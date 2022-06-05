/* malloc.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
  int x = 5; /* allocate 4 bytes (static allocation) on the runtime stack */

  int * y;   /* allocate 8 bytes (static allocation) on the stack */

#if 0
  *y = 100;  /* segmentation fault because y is uninitialized */
#endif

  /* dynamically allocate sizeof( int ) or 4 bytes on the runtime heap */
  y = malloc( sizeof( int ) );   /* man malloc */

  if ( y == NULL )
  {
    perror( "malloc() failed" );
    return EXIT_FAILURE;
  }

  *y = 100;

  printf( "x is %d\n", x );
  printf( "*y is %d\n", *y );

  free( y );


  /* TO DO: if I remove the above free() call, do I have a memory leak...? */


#if 0
  /* statically allocate an array of size 10 */
  int y[10];
#endif

  /* dynamically allocate an array of 10 integers */
  y = calloc( 10, sizeof( int ) );
    /* how many bytes does this calloc() call allocate? */
    /* -- we have an array of 10 elements, each element is 4 bytes */

  /* TO DO: check the return value from calloc() for error */

  y[4] = 1234;

  printf( "y[4] is %d\n", y[4] );

  /* the next two lines are equivalent */
  printf( "y[5] is %d\n", y[5] );
  printf( "y[5] is %d\n", *(y+5) );   /* <== pointer arithmetic */

                       /* y[5] is equivalent to *(y+5)             */
                       /*             or really *(y+5*sizeof(int)) */
                       /*                                    ^^^   */
                       /*  we know to use sizeof(int) here because */
                       /*   we know that y is declared as int * y  */


  free( y );

  return EXIT_SUCCESS;
}