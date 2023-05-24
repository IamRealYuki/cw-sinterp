#ifndef CW_LEXER_H
#define CW_LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct token
{
    struct token *next;
    char **tokens;
};

void lexemize(char *name_of_file, struct token *list);
#endif