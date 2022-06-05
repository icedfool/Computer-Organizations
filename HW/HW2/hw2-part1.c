#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX 100000
#define MAX_LEN 10000

struct char_count{
    char ch;
    int count;
};

int compare(const void *a, const void *b){
    return *(char*)a - *(char*)b;
}

//find printable unique characters in a string
char* printable_char(char* str,int size){
    char* new_str = calloc(MAX_LEN, sizeof(char));
    //first find all the characters in the data stream
    for (size_t i = 0; i < size; i++){
        char ch = str[i];
        bool exist = false;
        bool is_printable = false;
        //check if the character is printable
        if (isprint(ch) != 0){
            is_printable = true;
        }
        //check if the character is already in the new string
        for (size_t j = 0; j < strlen(new_str); j++){
            if (new_str[j] == ch){
                exist = true;
            }
        }
        //if the character is printable and not in the new string, add it to the new string
        if (exist == false && is_printable == true){
            new_str[strlen(new_str)] = ch;
        }
    }
    int length = strlen(new_str);
    qsort(new_str, length, sizeof(char), compare);
    return new_str;
}

int main(int argc, char *argv[]){
    int default_val = 0;
    //create two dynamic arrays, first one is to store the count, second one is to store the char content
    char *input = calloc(MAX, sizeof(char));
    char* line_content = calloc(MAX_LEN, sizeof(char));

    //read the data and store it into the array
    while (fgets(line_content,MAX_LEN,stdin)){
        int sizeLine = strlen(line_content);
        for (int i = 0; i < sizeLine; i++){
            input[default_val] = line_content[i];
            default_val++;
        }
    }
    
    int data_size = strlen(input);
    char* new_str = printable_char(input, data_size);
    int new_str_size = strlen(new_str);
    
    //create a dynamic array to store the count of each character
    struct char_count *struct_array= calloc(new_str_size, sizeof(struct char_count));
    for (int i = 0; i < new_str_size; i++){
        struct_array[i].ch = new_str[i];
        struct_array[i].count = 0;
    }
    //match the character in the data stream with the character in the new string
    for (int i = 0; i < strlen(input); i++){
        for (int j = 0; j < new_str_size; j++){
            if (input[i] == struct_array[j].ch){
                struct_array[j].count++;
            }
        }
    }
//if( strcmp(items[n], "ae") == 0 )
    if (argc > 1){
        for (int i = 0; i < new_str_size; i++){
            char *buffer = calloc(struct_array[i].count, sizeof(char));
            memset(buffer,'#',struct_array[i].count);
            printf("%c: %s\n", struct_array[i].ch, buffer);
            free(buffer);
        }
    }
    else{
        for (int i = 0; i < new_str_size; i++){
            printf("%c: %d\n", struct_array[i].ch, struct_array[i].count);
        }
    }
    //release the memory
    free(input);
    free(line_content);
    free(new_str);
    free(struct_array);
    
    return EXIT_SUCCESS;
}