#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 2048

static char TEST_FILE[] = "./Examples/Test/test1.hdy";

// store error messages
char ERROR_BUFFER[MAX_LINE_LENGTH];


// text files come in as a linked list of lines
typedef struct TextLine {
    char *text;
    struct TextLine *next;
} TextLine;


void print_code_details(TextLine *code) {
    int count = 0;
    while(code->next != NULL) {
        count++;
        code = code->next;
    }
    printf("This code has %i lines of code", count);
}

void print_code(TextLine *code) {
    while(code->next != NULL) {
        printf("%s", code->text);
        code = code->next;
}


void handle_args(int argc, char *argv[])
{
    for(int i = 0; i <= argc; i++) {
        // iterate through handle_args
        printf("%s", argv[i]);
    };
};

void error()
{
    puts(ERROR_BUFFER);
};

TextLine* read_file(char filename[])
{
    FILE *fptr;

    fptr = fopen(filename, "r");
    if(fptr == NULL) {
        sprintf(ERROR_BUFFER, "Filename %s not found", filename);
        error();
    };

    // create the first node
    TextLine *line_text = (TextLine *) malloc(sizeof(TextLine));
    line_text->next = NULL;
    // remember where we are
    TextLine *first = line_text;

    for(;;) {
        fgets(line_text->text, MAX_LINE_LENGTH, fptr);
        if(line_text->text == NULL) {
            return(first);
            fclose(fptr);
        };
        // not null, so add the line and move on
        line_text->next = (TextLine *) malloc(sizeof(TextLine));
        line_text = line_text->next;
    };
};


int main(int argc, char *argv[])
{
    TextLine *code;

    handle_args(argc, argv);
    code = read_file(TEST_FILE);
    return 0;
}
