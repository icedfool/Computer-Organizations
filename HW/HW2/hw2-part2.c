#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX 10000

//Reads the first line of the file, store it as the title name
char* read_title(FILE* fp){
    char* title = calloc(MAX, sizeof(char));
    char* new_title = calloc(33, sizeof(char));
    
    fgets(title, MAX, fp);
    strncpy(new_title, title, 33);
    new_title[strlen(new_title)-1] = '\0';

    free(title);
    return new_title;
}

// Reads the second line of the file, store it as the column num
int read_num(FILE* fp){
    char *content = calloc(MAX, sizeof(char));
    fgets(content, MAX, fp);
    int num = atoi(content);
    free(content);
    return num;
}

char read_char(FILE* fp){
    char *content = calloc(MAX, sizeof(char));
    fgets(content, MAX, fp);
    char c = content[0];
    free(content);
    return c;
}

//
char** readColumnTitle(FILE* fp, int num){
    char** column_content = calloc(num, sizeof(char*));
    for (int i = 0; i < num; i++){
        char *line = calloc(MAX, sizeof(char));
        column_content[i] = fgets(line, MAX, fp);
        char *Buffer = calloc(MAX, sizeof(char));
        //set the limit of the column title to 16
        Buffer = strncpy(Buffer, column_content[i],17);
        Buffer[strlen(Buffer)-1] = 0;
        free(line);
        column_content[i] = Buffer;
    }
    return column_content;
}

int markColumn(char** column_content, int num){
    int count = 0;
    for (int i = 0; i < num; i++){
        if (column_content[i][0] == 'N' && column_content[i][1] == 'u' &&\
            column_content[i][2] == 'm' && column_content[i][3] == 'b' && \
            column_content[i][4] == 'e' && column_content[i][5] == 'r'){
            count = i;
        }
    }
    return count;
}

int TitleOrContentBigger(char* title, int num){
    int bigger;
    if (strlen(title) > num){
        bigger = strlen(title);
        return bigger;
    }
    else{
        bigger = num;
        return bigger;
    }
}
char *** readColumnContent(FILE* fp, int num, int row, char** column_title, char PrintChar){
    fseek(fp, 0, SEEK_SET);
    char *** column_content = calloc(num, sizeof(char**));
    for (int i = 0; i < num; i++){
        column_content[i] = calloc(row, sizeof(char*));
    }
    for (int i = 0; i < row; i++){
        for (int j = 0; j < num; j++){
            column_content[j][i] = calloc(MAX, sizeof(char));
            char *line = calloc(MAX, sizeof(char));
            free(column_content[j][i]);
            column_content[j][i] = fgets(line, MAX, fp);
            column_content[j][i][strlen(column_content[j][i])-1]=0;
            //next determine if the column content is a number
            if (column_title[j][0] == 'N' && column_title[j][1] == 'u' && column_title[j][2] == 'm' && column_title[j][3] == 'b'\
                                          && column_title[j][4] == 'e' && column_title[j][5] == 'r'){
                //if it is a number, then convert it to string of the char to be printed
                int number = atoi(column_content[j][i]);
                free(column_content[j][i]);
                column_content[j][i] = calloc(number+1, sizeof(char));
                memset(column_content[j][i], PrintChar, number);
            }
        }
    }
    return column_content;
}

int findMaxLen(char** stringList, int num){
    int maxLen = 0;
    for (int i = 0; i < num; i++){
        if (strlen(stringList[i]) > maxLen){
            maxLen = strlen(stringList[i]);
        }
    }
    return maxLen;
}

//return the line number of the file
int fileLineCount(FILE* fp,int num){
    int count = 0;
    char *line = calloc(MAX, sizeof(char));
    while(fgets(line, MAX, fp)){
        count++;
    }
    free(line);
    count = count/num;
    return count;
}

void printTitleLine(char* title){
    printf("   ");
    printf("===");
    printf(" ");
    int size = strlen(title);
    for (int i = 0; i < size; i++){
        printf("%c", toupper(title[i]));
    }
    printf(" ");
    printf("===\n");
}

void printColumnTitleLine(char** column_title, int* MaxArray,int mark, int num){
    for (int i = 0; i < num; i++){
        //if this column is the number column, then print them to the left  
        if(i == mark){
            int numRight = MaxArray[i] - strlen(column_title[i]) - 1;
            printf(" ");
            printf("%s", column_title[i]);
            if (i < num-1){
                for (int j = 0; j < numRight; j++){
                    printf(" ");
                }
                printf("|");
            }
        }
        else{
            int numLeft = MaxArray[i] - strlen(column_title[i]) -1;
            for (int j = 0; j < numLeft; j++){
                printf(" ");
            }
            printf("%s", column_title[i]);
            if (i < num-1){
                printf(" ");
                printf("|");
            }
        }
    }
    printf("\n");
}

void printSeperatrLine(int* MaxArray, int num){
    for (int i = 0; i < num; i++){
        for (int j = 0; j < MaxArray[i]; j++){
            printf("-");
        }
        if (i < num-1){
            printf("|");
        }
    }
    printf("\n");
}

void printContentLine(char*** column_content, int* MaxArray, int mark, int num, int row){
    for (int i = 0; i < row; i++){
        for(int j = 0; j < num; j++){
            if(j == mark){
                int numRight = MaxArray[j] - strlen(column_content[j][i]) - 1;
                printf(" ");
                printf("%s", column_content[j][i]);
                
                if (j < num-1){
                    for (int k = 0; k < numRight; k++){
                        printf(" ");
                    }
                    printf("|");
                }
            }
            else{
                int numLeft = MaxArray[j] - strlen(column_content[j][i]) -1;
                for (int k = 0; k < numLeft; k++){
                    printf(" ");
                }
                printf("%s", column_content[j][i]);
                if (j < num-1){
                    printf(" ");
                    printf("|");
                }
            }
        }
        printf("\n");
    }
} 

int main(int argc, char *argv[]){
    //open two files
    FILE *fp1 = fopen(argv[1], "r");
    FILE *fp2 = fopen(argv[2], "r");
    if (fp1 == NULL){ 
        perror ("Error opening file");
        return EXIT_FAILURE;
    }
    if (fp2 == NULL){ 
        perror ("Error opening file");
        return EXIT_FAILURE;
    }
    fseek(fp1, 0L, SEEK_SET);
    fseek(fp2, 0L, SEEK_SET);

    //prpare the data that need to be printed
    char *title = read_title(fp1);
    int num_column = read_num(fp1);
    char char_content = read_char(fp1);
    char **column_title = readColumnTitle(fp1, num_column);
    int mark = markColumn(column_title, num_column);
    int row = fileLineCount(fp2, num_column);
    char ***column_content = readColumnContent(fp2, num_column, 
                                               row, column_title, char_content);

    int *maxArray = calloc(num_column, sizeof(int));
    //find the max length of the column content
    for (int i = 0; i < num_column; i++){
        maxArray[i] = findMaxLen(column_content[i], row);
        maxArray[i] = TitleOrContentBigger(column_title[i], maxArray[i]);
        maxArray[i] = maxArray[i] + 2;
    }
    //print the title line
    printTitleLine(title);
    printf("\n");
    printColumnTitleLine(column_title, maxArray, mark, num_column);
    printSeperatrLine(maxArray, num_column);
    printContentLine(column_content, maxArray, mark, num_column, row);
    printSeperatrLine(maxArray, num_column);

    free(title);
    for (int i = 0; i < num_column; i++){
        free(column_title[i]);
        for (int j = 0; j < row; j++){
            free(column_content[i][j]);
        }
        free(column_content[i]);
    }
    free(column_title);
    free(column_content);
    free(maxArray);
    fclose(fp1);
    fclose(fp2);
    return EXIT_SUCCESS;
}