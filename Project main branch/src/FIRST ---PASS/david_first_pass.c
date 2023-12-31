#include "/home/david/CLionProjects/My-project/Project main branch/src/FIRST ---PASS/header files/first_pass_headers.h"
#include "/home/david/CLionProjects/My-project/Project main branch/src/Error handling/errors.h"

/* TODO make sure that every number is macro based */



void first_pass(FILE *am_file, struct InstructionStructure *instructions_array, struct DataStructure *data_array,  Symbol *symbol_head, struct SymbolNameAndIndex **second_pass_list ) {
    char line[LEN];
    char words_array [LEN][LEN] = {0}; /* Initialize array */
    int index = 0;
    int symbol_definition = 0;
    int error_found = 0;
    int IC = 0;
    int DC = 0;
    int line_number = 0;
    char *word = NULL;
    char *current_symbol_name = NULL;


    while ( fgets(line,LEN ,am_file) ) {
        update_variables(&current_symbol_name, &symbol_definition,&line_number,&index);

        /* Check if the current line is a comment or an empty line if so skip it */
        if(comment_or_empty(line))
            continue;

        if (line_too_long(line)) {
            handle_error(LineLimitExceeded, line_number);
            error_found = 1;
            continue;
        }
        /* breaks the lines to separate words and stores them into words_array */
        format_and_store_words(line,words_array);
        word = words_array[index];

        /* Step 3 and 4 */
        if ( words_array[index + 1 ][0] == ':' ) {
            if ( is_valid_symbol(line, line_number,&error_found, words_array) ) {/* In this function we should output errors if found  */
                symbol_definition = 1;
                current_symbol_name = word; /* STR */
                index = index + 2; /* skip the name of the symbol and the char ':' */
                word = words_array[index];
            } else {
                continue;
            }
        }

        /* step 5 */    /*example: STR: .data 6,7,3,5,6,7,4  */
        if (is_directive(word,".string") || is_directive(word,".data")) {
            /* step 6 */
            if (symbol_definition)
                handle_symbol(&symbol_head, current_symbol_name, line_number, &error_found, DATA , NONE_CATEGORY, DC);
            /* if there was an error in with the symbol handling continue to next line */
            if(error_found)
                continue;

            /* step 7 */    /*example:  STR: .string     "abc , de fg"  */
            if ( is_directive(word,".string") ) {
                if ( valid_string_directive(line, line_number, &error_found,symbol_definition ) )
                    DC = DC + handle_string_directive(data_array, DC,line, line_number);
            } else { /* data directive */
                if ( valid_data_directive(words_array, line_number, &error_found,symbol_definition) )
                    DC = DC + handle_data_directive(data_array, DC, words_array, symbol_definition );
            }
            continue;
        }

        /* step 8 + 9*/   /*   M1: .extern STR,M2,M3  */
        if (is_directive(word,".extern") || is_directive(word,".entry")) {
            if ( !valid_entry_and_extern_directive(words_array, &error_found, line_number, symbol_definition) )
                continue;

            if (is_directive(word,".extern") )
                handle_extern_and_entry_directives(words_array,&symbol_head,symbol_definition,line_number, &error_found,NONE_TYPE,EXTERN);
            else
                handle_extern_and_entry_directives(words_array,&symbol_head,symbol_definition,line_number, &error_found, NONE_TYPE,ENTRY);
        }


        /* step 11 */
        if (symbol_definition)
            handle_symbol(&symbol_head, current_symbol_name,line_number,&error_found, CODE, NONE_CATEGORY, IC);

        /* step 12 + 13 + 14 */  /* example: STR: mov 5,M2 */
        if (valid_instruction(words_array, line_number, symbol_definition) )
            IC = IC + handle_valid_instruction(words_array, instructions_array,IC, symbol_definition, line_number, second_pass_list );
        else {/* the second word is not an instruction nor data/string directive than output error */
            /* here should be a function that can find more specific errors */
            error_found = 1;
            //handle_error(SomeErrorHere,line_number);
            continue;
        }
    }
    //handle_separation(symbol_head,IC,line_number,&error_found);
}















