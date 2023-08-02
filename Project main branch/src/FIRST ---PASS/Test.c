#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define LEN 200
#define ARRAY_SIZE 1024

/* in c90 standard minimum width of int is 16 bits so we can use the first 12 bits of it*/
struct DataStructure {
    int value : 12;
};
struct DataStructure* create_data_array(int size) {
    // Allocate memory for the array of DataStructure
    struct DataStructure* dataArray = (struct DataStructure*)malloc(size * sizeof(struct DataStructure));

    // Check if memory allocation is successful
    if (dataArray == NULL) {
        // Handle memory allocation failure if needed
        return NULL;
    }

    // Initialize the array elements (optional)
    for (int i = 0; i < size; i++) {
        dataArray[i].value = 0;
    }

    return dataArray;
}
void write_integer(struct DataStructure* data, int number) {
    // Ensure that the integer value fits within the 12-bit range
    if (number >= -2048 && number <= 2047) {
        data->value = number & 0xFFF; // Mask the value to keep only the 12 least significant bits (LSBs)
    } else {
        // Handle the case when the number is out of range for a 12-bit signed integer.
        // You can choose to set an error code or handle it differently as per your requirement.
    }
}
void write_character(struct DataStructure* data, char character) {
    // Reinterpret the character as an int16_t before storing it in the struct.
    data->value = (int)character;
}


/* EXAMPLE: STR: .string "hey! hey! you 2" */
int valid_string_directive(char words_array[LEN][LEN], int line_number, int *error_found){


}



int main(void) {
    struct DataStructure* data_array = create_data_array(ARRAY_SIZE);


    return 0;
}
