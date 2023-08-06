
int is_string_directive(char *word) {
    if (strcmp(word,".string") == 0)
        return 1;
    return 0;
}

int is_data_directive(char *word){
    if (strcmp(word,".data") == 0)
        return 1;
    return 0;
}

/* By the project definition valid characters are visible ASCI chars which are chars between 32 and 126 including in the ASCI table */
int is_valid_char(char c) {
    return (c >= 32 && c <= 126);
}

int is_valid_string(char *string, int length) {
    int i;
    for (i = 0; i < length; i++) {
        char current_char = string[i];
        if (current_char == '\\') {
            // Found backslash, skip the next character (it's valid)
            i++;
        } else if (current_char == '"') {
            // Found single quote without a preceding backslash, it's an error
            return 0;
        } else if (!is_valid_char(current_char)) {
            return 0;
        }
    }
    return 1;
}

int valid_string_directive(char words_array[LEN][LEN], int line_number, int *error_found, int symbol_definition) {
    char *string;
    int string_length = 0;
    int index = 1;

    if (symbol_definition)
        index++;

    string = words_array[index];
    string_length = strlen(string);

    /* Check if the word is an empty string */
    if (string_length == 0) {
        *error_found = 1;
        handle_error(EmptyStringDirective, line_number);
        return 0;
    }
        /* Check if there are any additional words after the string directive */
    else if (strcmp(words_array[index + 1], "") != 0) {
        *error_found = 1;
        handle_error(ExcessCharactersInDataLine, line_number);
        return 0;
    }
    else if (string[0] != '"') {
        *error_found = 1;
        handle_error(MissingStartOfStringSign, line_number);
        return 0;
    }
    else if (string_length == 1 || string_length > 1 && string[string_length - 1] != '"'){
        *error_found = 1;
        handle_error(MissingEndOfStringSign, line_number);
        return 0;
    }

        // Check the characters between the '"' characters (excluding the starting and ending '"')
    else {
        if (!is_valid_string(&string[1], string_length - 2)) {
            *error_found = 1;
            handle_error(InvalidCharInString, line_number);
            return 0;
        }
    }

    /* passed all checks */
    return 1;
}
