/* fgets.c */

/* To link in the math.h library:
 * bash$ gcc -Wall -Werror fgets.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{                  /*       [0]1 2 3 4  ...[31] */
                   /*       +-----------------+ */
  char name[32];   /* name: | | | | | | ... | | */
                   /*       +-----------------+ */

  /* Above, name is a pointer to the first byte of the array */


  /* note that name is uninitialized here: */
  printf( "name: %s\n", name );

  printf( "Enter your name: " );
/*  scanf( "%s", name ); */

  if ( fgets( name, 32, stdin ) == NULL )
  {
    fprintf( stderr, "ERROR: fgets() didn't work...\n" );
    return EXIT_FAILURE;
  }

  /* TO DO: Delete the trailing '\n' character, as well as
   *         trailing spaces, if any
   *
   *        HINT: assign '\0' to replace the '\n'
   *               (also use a loop to replace ' ' with '\0')
   */

  printf( "Hello \"%s\" (length is %ld)\n", name, strlen( name ) );

  /* TO DO: using strlen(), if we see the buffer is full, and the
   *         last character is not '\n' then we know there's more
   *          data on the stdin input stream
   *
   * To implement the above, maybe a loop using fgetc() to simply
   *  read and ignore the remaining bytes on the input line...
   *   ...until you see the ending '\n' character
   */

  return EXIT_SUCCESS;
}