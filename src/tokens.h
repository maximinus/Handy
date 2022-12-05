#pragma once

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 2048
#define MAX_TOKEN_LENGTH 512


enum TOKEN_TYPE {
    END,
    OPEN_BRACKET,
    CLOSE_BRACKET,
    VARIABLE,
    INTEGER,
    FLOAT,
    STRING,
    ERROR
};


// text files come in as a linked list of lines
typedef struct TextLine {
    char text[MAX_LINE_LENGTH];
    struct TextLine *next;
} TextLine;

TextLine* get_textline() {
    TextLine *line_text = (TextLine *) malloc(sizeof(TextLine));
    line_text->next = NULL;
    return line_text;
};


typedef struct CodeTokens {
    TextLine code;
    int line_index;
} CodeTokens;

CodeTokens *get_tokenizer(TextLine code) {
    CodeTokens *all_code = (CodeTokens *) malloc(sizeof(CodeTokens));
    all_code->code = code;
    all_code->line_index = 0;
    return all_code;
};

char get_char(CodeTokens *tokenizer) {
    return tokenizer->code.text[tokenizer->line_index];
};

bool next_character(CodeTokens *tokenizer) {
    // returns True if not at EOL
    char next = get_char(tokenizer);
    if(next == 0) {
            // end of line, move to next one if we can
            if(tokenizer->code.next == NULL) {
                // at end of code
                return false;
            };
            // move to next line and loop again
            tokenizer->code = *tokenizer->code.next;
            tokenizer->line_index = 0;
    } else {
        tokenizer->line_index++;
    };
    return true;
};


typedef struct Token {
    enum TOKEN_TYPE type;
    char text[1024];
} Token;

Token *get_token(enum TOKEN_TYPE t, char txt[]) {
    Token *new_token = (Token *) malloc(sizeof(Token));
    strcpy(new_token->text, txt);
    new_token->type = t;
    return new_token;
};


void consume_white_space() {
};

char *get_digits(CodeTokens *tokenizer) {
    // read forwards until all digits have been consumed and then return this string
    char *number_buffer = malloc(MAX_TOKEN_LENGTH * sizeof(char));
    int buffer_index = 0;
    char next = get_char(tokenizer);

    // we need to collect all the digits we can find and place them into a string to return
    // the first character is guarenteed to be a digit
    while(isdigit(next)) {
        number_buffer[buffer_index] = next;
        if(next_character(tokenizer) == false) {
            // end of tokens, so end of buffer
            number_buffer[buffer_index + 1] = 0;
            return number_buffer;
        }
        buffer_index++;
        next = get_char(tokenizer);
    };
    // the character we are looking at is not a digit
    return number_buffer;
};


Token *get_next_token(CodeTokens *tokenizer) {
    char next = get_char(tokenizer);

    if(next == ' ' || next == '\t' || next == '\n' || next == '\r') {
        consume_white_space();
    if(next == '(') {
        return get_token(OPEN_BRACKET, "(");
    if(next == ')') {
        return get_token(CLOSE_BRACKET, ")");
    if(isdigit(next)) {
        return get_token(INTEGER, get_digits(tokenizer));
    };
    return get_token(ERROR, "");
};

void get_all_tokens(CodeTokens *tokenizer) {
};
