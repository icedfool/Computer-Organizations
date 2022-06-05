/* hw1.c */
/* NAME: Hao Ding */
/* COMPILE: gcc -Wall -Werror -Wvla hw1.c -lm */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

/* dynamically allocate memory for rows x cols matrix of integers */

int ** matrix_alloc( int rows, int cols ){
    int ** matrix = calloc( rows, sizeof( int * ) );
    for ( int r = 0 ; r < rows ; r++ ){
        matrix[r] = calloc( cols, sizeof( int ) );
    }
    return matrix;
}

//return the digit of a num
int digitNum(int num){
    int count = 0;
    while(num != 0){
        num /= 10;
        ++count;
    }
    return count;
}

char** generate_line(int row, int column, int** matrix){
    int numSpace = column - 1;
    char** returnStringArray = calloc(row,sizeof (char * ));
    for (int i = 0; i < row; ++i) {
        int countLine = 0;
        for (int j = 0; j < column; ++j) {
            countLine += digitNum(matrix[i][j]);
            if(j != column-1){
                countLine += 2;
            }
        }
    }
}
int main( int argc, char * argv[] ){
/* Ensure we have the correct number of command-line arguments */
    if ( argc != 5 ){
        fprintf( stderr, "ERROR: Invalid inputs!\n" );
        return EXIT_FAILURE;
    }
    int rowMatrix1 = atoi(argv[1]);
    int columnMatrix1 = atoi(argv[2]);
    int rowMatrix2 = atoi(argv[3]);
    int columnMatrix2 = atoi(argv[4]);

    /* case that the two matrix can't multiply */
    if(columnMatrix1 != rowMatrix2){
        fprintf( stderr, "ERROR: Invalid inputs!\n" );
        return EXIT_FAILURE;
    }

    int** matrix1 = matrix_alloc(rowMatrix1,columnMatrix1);
    int** matrix2 = matrix_alloc(rowMatrix2,columnMatrix2);

    printf("Please enter non-negative integer values for the first matrix (%dx%d):\n",rowMatrix1,columnMatrix1);
    //scan the value into the first matrix
    for (int i = 0; i < rowMatrix1; ++i) {
        for (int j = 0; j < columnMatrix1; ++j) {
            scanf("%d",&matrix1[i][j]);
        }
    }
    printf("Please enter non-negative integer values for the second matrix (%dx%d):\n",rowMatrix2,columnMatrix2);
    //scan the value into the second matrix
    for (int i = 0; i < rowMatrix2; ++i) {
        for (int j = 0; j < columnMatrix2; ++j) {
            scanf("%d",&matrix2[i][j]);
        }
    }

    int** returnMatrix = matrix_alloc(rowMatrix1,columnMatrix2);
    for(int i=0;i<rowMatrix1;i++){
        for(int j=0;j<columnMatrix2;j++){
            for(int k=0;k<columnMatrix1;k++){
                returnMatrix[i][j] = returnMatrix[i][j] + matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    printf("%d\n",returnMatrix[0][0]);
    printf("%d\n",returnMatrix[1][0]);
    return EXIT_SUCCESS;
}
