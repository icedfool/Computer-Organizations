/* file-read.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
  int i, j, k;
  double gpa;

  char * filename = "xyz.txt";

  FILE * file = fopen( filename, "r" );

  if ( file == NULL )
  {
    perror( "fopen() failed" );
    return EXIT_FAILURE;
  }

  int rc = fscanf( file, "%d %d %d %lf\n", &i, &j, &k, &gpa );
  printf( "fscanf() returned %d values from the file.\n", rc );
  printf( "i = %d, j = %d, k = %d, gpa = %lf\n", i, j, k, gpa );

  /* TO DO: try the above with "bad" input values in the input file */

  /* TO DO: rewrite the above using fgets() and sscanf() */

  /* fread() */
  {
    double arr[10];
    rc = fread( arr, sizeof( double ), 10, file );
    printf( "fread() read %d double values from the file.\n", rc );
    printf( "fread() read %lu bytes from the file.\n", rc * sizeof( double ) );
    printf( "%lf %lf\n", arr[0], arr[1] );

    /* TO DO: write a quick for loop to display all values read in here... */
  }

  fclose( file );

}