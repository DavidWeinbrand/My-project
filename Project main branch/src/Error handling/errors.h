
#ifndef SPL2023B_PROJECT_COPY_ERRORS_H
#define SPL2023B_PROJECT_COPY_ERRORS_H
enum Error {
    NoError,
    ExcessCharactersAtStartMacro,
    ExcessCharactersAtEndMacro,
    InvalidMacroName,
    InvalidCharacterInName,
    FirstCharacterNotLetter,
    ReservedKeywordName,
    NameExceedsMaxLength,
    FailedToAllocateMemory,
    InvalidFormat,
    ExcessCharactersInDataLine,
    MissingStartOfStringSign,
    MissingEndOfStringSign,
    InvalidCharInString,
    LineLimitExceeded,
    CommaAtStart,
    ConsecutiveCommas,
    MissingComma,
    EndsWithComma,
    InvalidCharInDataDirective,
    IntegerOverflow,
    MultipleSymbolDefinition,
    NonWhiteCharsBeforeQuote,
    NonWhiteCharsAfterClosingQuote,



};



const char* errorMessages[] = {
        "No error",
        "Excess characters at the start of macro definition.",
        "Excess characters at the end of macro definition.",
        "Invalid macro name.",
        "Name contains an invalid character.",
        "First character is not a letter.",
        "Name is a reserved keyword.",
        "Name exceeds the maximum allowed length.",
        "Failed to allocate memory.",
        "Invalid Format for string directive.",
        "Excess characters in data line.",
        "Missing quotation mark at the start of the string.",
        "Missing quotation mark at the end of the string.",
        "Invalid character in string.",
        "Line limit Exceeded.",
        "Cannot start directive with comma.",
        "Two consecutive commas in line.",
        "Missing comma between parameters.",
        "Line cannot end with comma.",
        "Invalid character in data directive.",
        "Integer overflow occurred. The value is too large to be represented by 12 bits.",
        "Multiple symbols definition found.",
        "Invalid characters before opening quote, only white chars allowed.",
        "Non white characters after closing quote detected.",

};

void handle_error(enum Error error, int line_number) {
    if (error != NoError) {
        fprintf(stderr, "Error in line %d: %s\n", line_number, errorMessages[error]);
    }
}
#endif //SPL2023B_PROJECT_COPY_ERRORS_H
