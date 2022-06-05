#include <stdio.h>
#include <stdbool.h>
int main() {

    bool status = true;
    while (status == true) {
        printf("Enter n (or -1 to exit): ");
        int buffer;
        scanf("%d", &buffer);
        if (buffer == -1) {
            status = false;
        } else if (buffer <= 0) {
            printf("ERROR: invalid input; please try again\n");
            continue;
        } else if (buffer % 2 == 0) {
            printf("ERROR: invalid input; please try again\n");
            continue;
        } else {
            for (int i = 0; i <= buffer / 2; ++i) {
                int space_num = buffer / 2 - i;
                for (int j = 0; j < space_num; ++j) {
                    printf("%c", ' ');
                }
                for (int l = 0; l < buffer - 2 * space_num; ++l) {
                    printf("%c", '*');
                }
                printf("%c", '\n');
            }
            for (int i = 0; i < buffer / 2; ++i) {
                int space_num2 = i + 1;
                for (int j = 0; j < space_num2; ++j) {
                    printf("%c", ' ');
                }
                for (int l = 0; l < buffer - 2 * space_num2; ++l) {
                    printf("%c", '*');
                }
                printf("%c", '\n');
            }
            continue;
        }

    }
    return 0;
}