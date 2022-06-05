/* pointers.c */

/* TO DO: extend the Fibonacci code to calculate the Fibonacci sequence
 *         out to 50 values, i.e., extend the array from size 10 to 50
 *
 *        the int data type is only 4 bytes, so also change/extend the
 *         code to use a long data type (8 bytes) for the array instead
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* function prototype */
void print_int_array( int * array, int length );


int main()
{
  int answer = 42;
  int * ptr;

  ptr = &answer;  /* & is the address-of operator */

#if 0
  ptr:              answer:
   +--------+        +----+
   | <addr> ========>| 42 |
   +--------+        +----+
    8 bytes          4 bytes
#endif

  printf( "answer is %d\n", answer );
  printf( "&answer is %p\n", &answer );
  printf( "&ptr is %p\n", &ptr );
  printf( "ptr is %p\n", ptr );
  printf( "*ptr is %d\n", *ptr );  /*  * is the dereference operator */

  printf( "sizeof( answer ) is %lu bytes\n", sizeof( answer ) );
  printf( "sizeof( ptr ) is %lu bytes\n", sizeof( ptr ) );


  int fib[10];
  printf( "sizeof( fib ) is %lu bytes\n", sizeof( fib ) );

#if 0
  printf( "fib[20] is %d\n", fib[20] );  /*  *(fib+20)  */
  printf( "fib[10000] is %d\n", fib[10000] );  /*  *(fib+10000)  */
  /* the first line above will display garbage data */
  /* the second line above will (most likely) cause a seg fault */
#endif

#if 0
   fib:
     [0]  [1]  [2]  [3]  [4]  [5]  [6]  [7]  [8]  [9]
    +----+----+----+----+----+----+----+----+----+----+
    |    |    |    |    |    |    |    |    |    |    |
    +----+----+----+----+----+----+----+----+----+----+
     int 40 bytes (4 x 10) .... long 80 bytes (8 x 10)
#endif

  fib[0] = 0;   /*  *(fib+0) = 0;  */
  fib[1] = 1;   /*  *(fib+1) = 1;  */

  for ( int i = 2 ; i < 10 ; i++ )
  {
    fib[i] = fib[i-2] + fib[i-1];   /*  *(fib+i) = ... <== TO DO  */
  }

  print_int_array( fib, 10 );

  printf( "fib[6] is %d\n", fib[6] );
  printf( "fib[6] is %d\n", *(fib + 6) );   /* pointer arithmetic */

  printf( "&fib is %p\n", &fib );
  printf( "&fib[0] is %p\n", &fib[0] );  /*  &(*(fib + 0))  */
  printf( "&fib[1] is %p\n", &fib[1] );
  printf( "fib + 2 is %p\n", fib + 2 );
  printf( "&fib[3] is %p\n", &fib[3] );


#if 0
   fib:
     [0]  [1]  [2]  [3]  [4]  [5]  [6]  [7]  [8]  [9]
    +----+----+----+----+----+----+----+----+----+----+
    |    |    |    |    |    |    |    |    |    |    |
    +----+----+----+----+----+----+----+----+----+----+
     int 40 bytes (4 x 10) .... long 80 bytes (8 x 10)
#endif

  /* recalculate Fibonacci numbers using only pointers and
      pointer arithmetic: */
  memset( fib, 0, sizeof( fib ) );

  int * x = fib;   /* x will point to each cell/element of the fib array */
  int * endaddr = x + 10;
  printf( "fib is %p\n", fib );
  printf( "x is %p\n", x );
  printf( "endaddr is %p\n", endaddr );

  *x = 0;   /* fib[0] = 0; */
  x++;      /* this moves the pointer fwd by sizeof( int ) or 4 bytes */
  *x = 1;   /* fib[1] = 1; */
  x++;

  while ( x < endaddr )
  {
    *x = *(x - 2) + *(x - 1);   /* fib[i] = fib[i-2] + fib[i-1]; */
    x++;
  }

  print_int_array( fib, 10 );

  return EXIT_SUCCESS;
}


                   /* int array[] */
void print_int_array( int * array, int length )
{
  for ( int i = 0 ; i < length ; i++ )
  {
    printf( "array[%d] is %d\n", i, array[i] );   /*  *(array+i)  */
  }
}