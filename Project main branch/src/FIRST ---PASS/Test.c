#include "/home/david/CLionProjects/My-project/Project main branch/src/FIRST ---PASS/header files/first_pass_headers.h"
#include "/home/david/CLionProjects/My-project/Project main branch/src/Error handling/errors.h"


/* TESTING HERE */

int is_reserved_keyword(const char *word) {
    for (size_t i = 0; i < sizeof(reservedKeywords) / sizeof(reservedKeywords[0]); i++) {
        if (strcmp(word, reservedKeywords[i]) == 0) {
            return 1; /* Found a match, it's a reserved keyword */
        }
    }
    return 0; /* No match, it's not a reserved keyword */
}
int is_symbol(const char *symbol) {
    size_t i = 1;

    if (is_reserved_keyword(symbol))
        return 0;

    if (symbol == NULL || strlen(symbol) > 31 || strlen(symbol) == 0) {
        return 0; /* Invalid if NULL, longer than 31 chars, or empty */
    }

    if (!isalpha(symbol[0])) {
        return 0; /* Symbol must start with a letter */
    }

    for ( i; symbol[i] != '\0'; i++) {
        if ( !isalnum(symbol[i]) ){
            return 0; /* Invalid character in the symbol */
        }
    }

    return 1; /* The string satisfies the criteria for a valid symbol */
}
int valid_commas_in_directive(char words_array[LEN][LEN], int starting_index, int line_number) {
    int i = starting_index;

    /* Check if the first word is a comma */
    if (words_array[i][0] == ',') {
        handle_error(CommaAtStart,line_number);  /* Comma at start */
        return 0;  /* Invalid */
    }

    i++;  /* Move to the next word */

    /* Iterate through the words */
    while (words_array[i][0] != '\0') {
        /* Check if the current word is a comma */
        if (words_array[i][0] == ',') {
            /* Check for consecutive commas */
            if (words_array[i - 1][0] == ',') {
                handle_error(ConsecutiveCommas,line_number);  /* 2 consecutive commas */
                return 0;  /* Invalid */
            }
        } else {
            /* Check if the previous word is not a comma */
            if (words_array[i - 1][0] != ',') {
                handle_error(MissingComma,line_number);  /* Comma expected after a word */
                return 0;  /* Invalid */
            }
        }

        i++;  /* Move to the next word */
    }

    /* Check if the last word is a comma */
    if (words_array[i - 1][0] == ',') {
        handle_error(EndsWithComma,line_number);  /* Ends with comma error */
        return 0;  /* Invalid */
    }

    return 1;  /* Valid */
}

/* STR : .extern M1 , M2 , M3 */
int valid_extern_directive(char words_array[LEN][LEN], int *error_found, int line_number, int symbol_definition){
    int index = 1;

    /* if there is symbol definition skip the name of the symbol and ':' char */
    if(symbol_definition)
        index = index + 2;

    if( !valid_commas_in_directive(words_array,index,line_number) ){
        *error_found = 1;
        return 0;
    }

    if (words_array[index][0] == '\0'){
        *error_found = 1;
        handle_error(InvalidNumberOfOperands,line_number);
        return 0;
    }

    while ( words_array[index][0] != '\0'){
        if( !is_symbol(words_array[index]) ){
            *error_found = 1;
            handle_error(OnlySymbolsAllowed,line_number);
            return 0;
        }
        /* check the next parameter, skipping the: ',' char */
        index = index + 2;
    }
    /* passed all checks */
    return 1;
}

void handle_extern_directive(char words_array[LEN][LEN], SymbolTable *table, int symbol_definition){
    int index = 1;

    if(symbol_definition)
        index = index + 2;

    while (words_array[index][0] != '\0'){
        add_symbol(&table,words_array[index],0,EXTERN);
        index = index + 2;
    }
}




int main() {
    char words_array[LEN][LEN] = { "STR", ":", ".extern",   };
    int error = 1;
    if (valid_extern_directive(words_array,&error,1,1))
        printf("valid");
    return 0;
}



