#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#define MAX 1024

//return a array that contains 2 to 0 to 2 to 10(1024)
int* TwoPowArray(){
    int* returnArray = calloc(20,sizeof(int));
    for (int i = 0; i < 10; ++i) {
        returnArray[i] = pow(2,i);
    }
    return returnArray;
}

int findIndex(char target, char** array){
    int returnIndex = 0;
    for (int i = 0; i < MAX; i++){
        if(array[i][0] == target){
            returnIndex = i;
            break;
        }
    }
    return returnIndex;
}

void processLineData(char* lineContent, char** varibleInput){
    char * pch;
    char  **varible = calloc(1024,sizeof(char* )); // REMEMBER TO FREE THIS
    pch = strtok (lineContent," ");
    int i = 0;
    //get all content in a line into the varible array
    while (pch != NULL){
        varible[i] = pch;
        pch = strtok (NULL, " ,;");
    }
    //if current line is declaring variable line, then store them into the varibleInput array
    if(varible[0] == "int"){
        int size = sizeof(varible)/sizeof(varible[0]);
        if(varibleInput[0] == NULL){
            for (int i = 1; i < size; ++i) {
                varibleInput[i-1] = varible[i];
            }
        }
        //if current index already have content inside , then keep going until a empty space is
        //found.
        else{
            int marker = 0;
            while (varibleInput[marker] != NULL){
                marker++;
            }
            for (int i = 1; i < size; ++i) {
                varibleInput[marker] = varible[i];
            }
        }
    }
    //if current line is assignment line, then store them into the varibleInput array
    if(varible[1] == "=" && (isdigit(varible[2])) != 0){
        printf("ori $t0, $0, %s\n",varible[2]);
        int index = findIndex(varible[0][0],varibleInput);
        index *= 4;
        printf("sw $t0,%d($a0)",index);
    }
    else{
        int size = sizeof(varible)/sizeof(varible[0]);
        //first find the index of the return varible
        if(isalpha(varible[0]) != 0){
            int swIndex = findIndex(varible[0][0],varibleInput);
        }
        //array and marker to assist
        char** varibleArray = calloc(1024,sizeof(char*));// REMEMBER TO FREE THIS
        char* operatorArray = calloc(1024,sizeof(char));// REMEMBER TO FREE THIS
        int numArray[1024];
        int variblemarker = 0;
        int operatormarker = 0;
        int nummarker = 0;
        //then we loop through the rest of the varible to find the index of the varible
        for (int i = 0; i < size; i++){
            if(isdigit(varible[i]) != 0){
                numArray[nummarker] = atoi(varible[i]);
                nummarker++;
            }
            else if(isalpha(varible[i]) != 0){
                varibleArray[variblemarker] = varible[i];
                variblemarker++;
            }
            else{
                operatorArray[operatormarker] = varible[i][0];
                operatormarker++;
            }
        }
        int tempregister = 0;
        int tempRegArray[1024];
        int *twoPowArray = TwoPowArray();
        for(int i = 2; i < size; i++ ){
            //make sure this is not the last varible
            if(i != size - 1 ){
                if(isalpha(varible[i]) != 0){
                    int index = findIndex(varible[i][0],varibleInput);
                    index *= 4;
                    printf("lw $t%d,%d($a0)",tempregister,index);
                    tempRegArray[tempregister] = tempregister;
                    tempregister++;
                    continue;
                }
                //case like y + 1
                else if(isdigit(varible[i]) != 0 && varible[i-1] == "+"){
                    printf("addi $t%d,$t%d,%d\n",tempregister,tempRegArray[tempregister-1],atoi(varible[i]));
                    tempRegArray[tempregister] = tempregister;
                    tempregister++;
                    continue;
                }
                //cases like 1 + y
                else if(isalpha(varible[i]) != 0 && varible[i-1] == "+"){
                    int index = findIndex(varible[i][0],varibleInput);
                    printf("lw $t%d,%d($a0)",tempregister,index*4);
                    tempRegArray[tempregister] = tempregister;
                    tempregister++;
                    printf("add $t%d,$t%d,$t%d\n",tempregister,tempRegArray[tempregister-2],tempRegArray[tempregister-1]);
                    tempRegArray[tempregister] = tempregister;
                    tempregister++;
                    continue;
                }
                //case like y - 1
                else if(isdigit(varible[i]) != 0 && varible[i-1] == "-"){
                    printf("addi $t%d,$t%d,-%d\n",tempregister,tempRegArray[tempregister-1],atoi(varible[i]));
                    tempRegArray[tempregister] = tempregister;
                    tempregister++;
                    continue;
                }
                //case like x + y
                else if(isalpha(varible[i]) != 0 && varible[i-1] == "+"){
                    int index = findIndex(varible[i][0],varibleInput);
                    printf("lw $t%d,%d($a0)",tempregister,index*4);
                    tempRegArray[tempregister] = tempregister;
                    tempregister++;
                    printf ("add $t%d,$t%d,$t%d\n",tempregister,tempRegArray[tempregister-2],tempRegArray[tempregister-1]);
                    continue;
                }
                //case like x - y
                else if(isalpha(varible[i]) != 0 && varible[i-1] == "-"){
                    int index = findIndex(varible[i][0],varibleInput);
                    printf("lw $t%d,%d($a0)",tempregister,index*4);
                    tempRegArray[tempregister] = tempregister;
                    tempregister++;
                    printf ("sub $t%d,$t%d,$t%d\n",tempregister,tempRegArray[tempregister-2],tempRegArray[tempregister-1]);
                    continue;
                }
                //cases like x*7
                else if(isdigit(varible[i] != 0) && varible[i-1] == "*"){
                    int index = findIndex(varible[i][0],varibleInput);
                    printf("lw $t%d,%d($a0)",tempregister,index*4);
                    tempRegArray[tempregister] = tempregister;
                    tempregister++;
                    int temp = atoi(varible[i]);
                    //here we use twoPowArray to find the sum of power of the number
                    for (int i = 10; i >= 0; i--){
                        int breakcounter = 0;
                        while (breakcounter != 2){
                            if(temp > twoPowArray[i]){
                                printf("sll $t%d,$t%d,%d\n",tempregister,tempRegArray[tempregister-1],i);
                                tempRegArray[tempregister] = tempregister;
                                tempregister++;
                                breakcounter++;
                            }
                        }
                        
                    }
                    
                }
            }
            //when it is the last char, we need to findout the index of the varible on the left
            else{
                int index = findIndex(varible[i][0],varibleInput);
                index *= 4;
                //if the final varible is a digit, then we need to add it to the register
                if(isdigit(varible[i]) != 0 && varible[i-1] == "+"){
                    printf("addi $t%d,$t%d,%d\n",tempregister,tempRegArray[tempregister-1],atoi(varible[i]));
                    printf("sw $t%d,%d($a0)",tempregister,index);
                }
                //if the final varible is a digit, then we need to sub it to the register(x-1)
                else if (isdigit(varible[i]) != 0 && varible[i-1] == "-"){
                    printf("addi $t%d,$t%d,-%d\n",tempregister,tempRegArray[tempregister-1],atoi(varible[i]));
                    printf("sw $t%d,%d($a0)",tempregister,index);
                }
                // cases like x+y
                else if(isalpha(varible[i]) != 0 && varible[i-1] == "+"){
                    int index = findIndex(varible[i][0],varibleInput);
                    printf("lw $t%d,%d($a0)",tempregister,index*4);
                    printf("add $t%d,$t%d,$t%d\n",tempregister,tempRegArray[tempregister-2],tempRegArray[tempregister-1]);
                    printf("sw $t%d,%d($a0)",tempregister,index);
                }
                //cases like x-y
                else if(isalpha(varible[i]) != 0 && varible[i-1] == "-"){
                    int index = findIndex(varible[i][0],varibleInput);
                    printf("lw $t%d,%d($a0)",tempregister,index*4);
                    printf("sub $t%d,$t%d,$t%d\n",tempregister,tempRegArray[tempregister-2],tempRegArray[tempregister-1]);
                    printf("sw $t%d,%d($a0)",tempregister,index);
                }
            }
        }
        free(varible);
        free(varibleInput);
    }
}

int main(int argc, char* argv[]){
    if (argc < 2) {
        fprintf(stderr, "Invalid input,please check.\n");
        return EXIT_FAILURE;
    }
    // Open input file
    char const* const fileName = argv[1];
    FILE * myfile;
    char ** varible = calloc(1024,sizeof(char* ));//collect all varible, REMEMBER TO FREE THIS
    myfile = fopen(fileName, "r");
    //check if the open file is successful
    if (!myfile) {
        fprintf(stderr, "Cannot open file, please check.\n");
        return EXIT_FAILURE;
    }
    //create a buffer with a size of 255
    const int bufferLength = 255;
    char buffer[bufferLength];
    //open file
    myfile = fopen("file.txt", "r");

    while(fgets(buffer, bufferLength, myfile)) {
        printf("# %s\n", buffer);
        processLineData(buffer);
    }

    fclose(myfile);
    free(varible);
    return EXIT_SUCCESS;
}