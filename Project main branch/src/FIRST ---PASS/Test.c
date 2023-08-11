#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "/home/david/CLionProjects/My-project/Project main branch/src/Error handling/errors.h"
#include <ctype.h>
#define LEN 200
#define ARRAY_SIZE 1024

/* in c90 standard minimum width of int is 16 bits so we can use the first 12 bits of it*/
struct DataStructure {
    int value : 12;
};




int main() {
    struct DataStructure data_array[100];  // Assuming an array of DataStructure

    char line[] = "STR: .string \"Hello, World!\"";
    int line_number = 1;
    int DC = 0;

    int chars_inserted = handle_string_directive(data_array, DC, line, line_number);
    printf("Chars inserted: %d\n", chars_inserted);

    // Print the data_array content for testing purposes
    for (int i = 0; i < chars_inserted; i++) {
        printf("data_array[%d].value: %c\n", i, (char)data_array[i].value);
    }

    return 0;
}

//TODO free after handle data and handle_data doesnt return the right amount of chars inserted
//TODO change the handle_string function, need to pass not the formatted line but the original