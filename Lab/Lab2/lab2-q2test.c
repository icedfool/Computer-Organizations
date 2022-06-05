#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

// this program reads the dat file and print the items:

// Steps:
//  1. Finding the size:
//  2. Reading the item into heap memory, them display the data using a loop:
//  3. fopen(), ftell(), calloc(), fread(), fclose(), and free(). Further, you must call the fseek() function exactly twice.

// this function is to find the size of the given file:
long int finding_size(char input_file[])
{
    FILE *fp = fopen(input_file, "r");

    if (fp == NULL)
    {
        perror("File Not Found. \n");
        return EXIT_FAILURE;
    }

    fseek(fp, 0L, SEEK_END);

    long int res = ftell(fp);

    fclose(fp);

    return res;
}

void print_file(char input_file[])
{
    FILE *fp = fopen(input_file, "rb");

    long int size = finding_size (input_file); 

    unsigned int * sample = calloc (size, sizeof(unsigned int));
    fseek(fp, 0, SEEK_SET); 
    fread (sample, size, 1, fp); 


    for (int i = 0; i < size / sizeof(int); i++) {
        printf ("DATA POINT #  %d: <%d> \n", i, sample[i]); 
    }

    fclose(fp);
    free(sample);

}

int main(int argc, char *argv[])
{

    // This part is to find out the size of the given file:
    long size = finding_size(argv[1]);
    printf("The size of this file is: %ld \n", size);

    // This part is to find Read The file and print out in the requred form:
    print_file (argv[1]);

    return EXIT_SUCCESS;
}
