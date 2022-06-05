/* hw1.c */
/* NAME: Hao Ding */
/* COMPILE: gcc -Wall -Werror -Wvla hw1.c -lm */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* dynamically allocate memory for rows x cols matrix of integers */

int ** matrix_alloc( int rows, int cols ){
    int ** matrix = calloc( rows, sizeof( int * ) );
    for ( int r = 0 ; r < rows ; r++ ){
        matrix[r] = calloc( cols, sizeof( int ) );
    }
    return matrix;
}

void free_matrix( int ** matrix, int rows){
    for ( int r = 0 ; r < rows ; r++ ){
        free(matrix[r]);
    }
    free( matrix );
}

void free_format( int* format){
    free( format );
}

//helper function to find the bigger value
int Max( int a, int b ){
    if (a > b)
        return a;
    else
        return b;
}
//helper function to find the smaller value
int Min( int a, int b ){
    if (a > b)
        return b;
    else
        return a;
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

//return the digit of a line of the matrix, return type is int*
int* getHighestDigit(int** matrix, int rows, int cols){
    int* heightDigit = calloc(cols, sizeof(int));
    for(int i = 0; i < cols; i++){
        int max = 0;
        for(int j = 0; j < rows; j++){
            if(matrix[j][i] > max){
                max = matrix[j][i];
            }
        }
        heightDigit[i] = digitNum(max);
    }
    return heightDigit;
}

//print the content of one line of the matrix
void generate_line(int row, int column, int** matrix, int* spaceFormat){
    for (int i = 0; i < column; i++){
        int space = spaceFormat[i];
        if (i == 0 && column == 1){
            printf("[%*i]", space,matrix[row][i]);//when there is only one column in the matrix
        }
        else if (i==0 && column != 1){
            printf("[%*i  ", space, matrix[row][i]);//when it is at the first column of the matrix
        }
        else if (i == column - 1){
            printf("%*i]", space, matrix[row][i]);//when it is at the last column of the matrix
        }
        else{
            printf("%*i  ", space, matrix[row][i]);//when it is in the middle of the matrix
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

    //generate the return matrix
    int** returnMatrix = matrix_alloc(rowMatrix1,columnMatrix2);
    for(int i=0;i<rowMatrix1;i++){
        for(int j=0;j<columnMatrix2;j++){
            for(int k=0;k<columnMatrix1;k++){
                returnMatrix[i][j] = returnMatrix[i][j] + matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    
    int* spaceFormat1 = getHighestDigit(matrix1, rowMatrix1, columnMatrix1);
    int* spaceFormat2 = getHighestDigit(matrix2, rowMatrix2, columnMatrix2);
    int* spaceFormatReturn = getHighestDigit(returnMatrix, rowMatrix1, columnMatrix2);
    int rowNumSamll = Min(rowMatrix1,rowMatrix2);
    int rowNumBig = Max(rowMatrix1,rowMatrix2);
    
    printf("\nRESULTS:\n");
    for (int i = 0; i < rowNumSamll; i++){
        //print the first matrix
        generate_line(i, columnMatrix1, matrix1, spaceFormat1);
        if (i == 0){
            printf(" multiplied by ");
        }
        else{
            printf("               ");
        }
        //print the second matrix
        generate_line(i, columnMatrix2, matrix2, spaceFormat2);
        printf("\n");
    }

    // if two matrix have same row number, print the return matrix
    if (rowNumSamll == rowNumBig){
        for (int i = 0; i < rowMatrix1; i++){
            if (i == 0){
                printf("equals ");
            }
            else{
                printf("       ");
            }
            generate_line(i, columnMatrix2, returnMatrix, spaceFormatReturn);
            printf("\n");
        }
        
    }
    else{
        //case 1 : the second matrix has more row
        if(rowMatrix1 < rowMatrix2){
            int spaceNum = 2;
            for (int i = 0; i < columnMatrix1; i++){
                spaceNum += spaceFormat1[i];
                if(i != columnMatrix1 - 1){
                    spaceNum += 2;
                }
            }
            
            for (int i = rowMatrix1; i < rowMatrix2; i++){
                printf("%*c", spaceNum, ' ');
                printf("               ");
                generate_line(i, columnMatrix2, matrix2, spaceFormat2);
                printf("\n");
            }
            for (int i = 0; i < rowMatrix1; i++){
                if (i == 0){
                    printf("equals ");
                }
                else{
                    printf("       ");
                }
                generate_line(i, columnMatrix2, returnMatrix, spaceFormatReturn);
                printf("\n");
            }
        }
        else{
        //case 2 : the first matrix has more row
            int spaceNum = 2;
            for (int i = 0; i < columnMatrix1; i++){
                spaceNum += spaceFormat1[i];
                if(i != columnMatrix1 - 1){
                    spaceNum += 2;
                }
            }
            
            for (int i = rowMatrix2; i < rowMatrix1; i++){
                generate_line(i, columnMatrix1, matrix1, spaceFormat1);
                printf("               " );
                printf("%*c", spaceNum, ' ');
                printf("\n");
            }
            for (int i = 0; i < rowMatrix1; i++){
                if (i == 0){
                    printf("equals ");
                }
                else{
                    printf("       ");
                }
                generate_line(i, columnMatrix2, returnMatrix, spaceFormatReturn);
                printf("\n");
            }
        }
    }
    free_matrix(matrix1,rowMatrix1);
    free_matrix(matrix2,rowMatrix2);
    free_matrix(returnMatrix,rowMatrix1);
    free_format(spaceFormat1);
    free_format(spaceFormat2);
    free_format(spaceFormatReturn);
}
