#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "src/tokens.h"


static char TEST_FILE[] = "../Examples/Test/test1.hdy";

// store error messages
char ERROR_BUFFER[MAX_LINE_LENGTH];


void print_code_details(TextLine *code) {
    int count = 0;
    while(code->next != NULL) {
        count++;
        code = code->next;
    };
    printf("This code has %i lines of code", count);
};

void print_code(TextLine *code) {
    while(code->next != NULL) {
        printf("%s", code->text);
        code = code->next;
    };
};


void handle_args(int argc, char *argv[]) {
    for(int i = 0; i <= argc; i++) {
        // iterate through handle_args
        printf("%s", argv[i]);
    };
};

void error() {
    puts(ERROR_BUFFER);
};


TextLine* read_file(char filename[]) {
    FILE *fptr;

    fptr = fopen(filename, "r");
    if(fptr == NULL) {
        sprintf(ERROR_BUFFER, "\nFilename %s not found", filename);
        error();
        return NULL;
    };

    // create the first node
    TextLine *line_text = get_textline();
    // remember where we are
    TextLine *first = line_text;

    while(fgets(line_text->text, MAX_LINE_LENGTH, fptr) != NULL) {
        line_text->next = get_textline();
        line_text = line_text->next;
    };
    fclose(fptr);
    return(first);
};


int main(int argc, char *argv[])
{
    TextLine *code;
;
    // handle_args(argc, argv);
    code = read_file(TEST_FILE);
    if(code != NULL) {
        print_code(code);
    } else {
        puts("Failed");
    }
    return 0;
}
