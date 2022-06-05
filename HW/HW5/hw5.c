#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

int doesexist(char target, char *arr) {
    int i = 0;
    
    while(arr[i]) {
        if (target == arr[i]) return i;
        i++;
    }
    arr[i] = target;
    return i;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Invalid input,please check.\n");
        return EXIT_FAILURE; 
    }
    // Open input file
    char const* const fileName = argv[1];
    FILE * myfile;
    myfile = fopen(fileName, "r");

    // check if the file can be opened
    if (!myfile) {
        fprintf(stderr, "Cannot open file, please check.\n");
        return EXIT_FAILURE;
    } 

    char * saved = malloc(9 * sizeof(char));
    char * equation = malloc(128 * sizeof(char));
    char line[128];

    int i, j, operationCount, numTemp1, numTemp2, isAssignment, numIndex, initial, k=0, tCount=0;
    int savedIndex;
    int leftnum1, leftnum2, rightnum1, rightnum2,rightNeg, initNeg, hastemp;
    

    while (fgets(line, sizeof(line), myfile)) {
        i = j = operationCount = numTemp1 = numTemp2 = isAssignment = numIndex = initial = hastemp = 0;
        printf("# %s", line);

        // Eliminate all spaces
        while (line[i] != '\0') {
            if (isspace(line[i])) {
                i++;
            } else {
                equation[j++] = line[i++];
            }
        }
        
        savedIndex = doesexist(equation[0], saved);
        
        i=2, j=3, k=4;

        do {
            leftnum1 = leftnum2 = rightnum1 = rightnum2 = rightNeg = initNeg = -1;
            // If equation[i] is '-'
            if (equation[i] == '-') {
                initNeg = 1;
                i++;
            }

            // If equation[i] is a digit
            if (isdigit(equation[i]) != 0) {
                leftnum1 = 0;
                leftnum2 = equation[i] - '0';
                while (isdigit(equation[i]) != 0) {
                    leftnum1 = leftnum1*10 + leftnum2;
                    i++;
                    leftnum2 = equation[i] - '0';
                }
                j = i;
                k = i + 1;
            }
            
            // If equation[k] is a minus sign
            if (equation[k] == '-') {
                rightNeg = 1;
                k++;
            }

            // If equation[k] is a digit
            if (isdigit(equation[k]) != 0) {
                rightnum1 = 0;
                rightnum2 = equation[k] - '0';
                while (isdigit(equation[k]) != 0) {
                    rightnum1 = rightnum1*10 + rightnum2;
                    k++;
                    rightnum2 = equation[k] - '0';
                }
                k--;
            }

            // If equation[i] is ';', then it comes to the end of this equation
            if (equation[j] == ';' && initial == 0) {
                // If this is negative
                if (initNeg == 1) {
                    printf("ori $s%d,$0,-%d\n", savedIndex, leftnum1);
                } 
                else {
                    printf("ori $s%d,$0,%d\n", savedIndex, leftnum1);
                }
                break;
            } 
            
            //=========================================== If addiction or subtraction ======================================
            if (equation[j] == '-' || equation[j] == '+') {
                if (equation[j] == '-'){
                    printf("sub ");
                } else if (equation[j] == '+') {
                    printf("add ");
                }
                
                // If it comes to the end of the equation
                if (equation[k+1] == ';') {
                    printf("$s%d,", savedIndex);

                    if (tCount == 10) {
                        printf("$t9,");
                        tCount = 0;
                    } else if (initial == 0) {
                        printf("$s%d,", doesexist(equation[i], saved));
                        initial++;
                    } else {
                        printf("$t%d,", tCount-1);
                    }

                    if (rightnum1 >= 0) {
                        printf("%d\n", rightnum1);
                    } else {
                        printf("$s%d\n", doesexist(equation[k], saved));
                    }
                } 
                else {
                    if (tCount == 10) {
                        printf("$t0,$t9,");
                        tCount = 1;
                    }
                    else if (initial == 0) {
                        printf("$t%d,", tCount);
                        tCount++;
                        initial++;
                        printf("$s%d,", doesexist(equation[i], saved));
                    } else {
                        printf("$t%d,$t%d,", tCount, tCount-1);
                        tCount++;
                    }
                    if (rightnum1 >= 0) {
                        printf("%d\n", rightnum1);
                    } else {
                        printf("$s%d\n", doesexist(equation[k], saved));
                    }
                    
                }
                
            }

            i = k;
            j = i + 1;
            k = j + 1;
            initial++;
            
        } while (equation[j] != ';' || equation[j] == '\0');
        
    }

    fclose(myfile);

    free(saved);
    free(equation);

    return EXIT_SUCCESS;
}