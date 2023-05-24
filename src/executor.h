#ifndef EXECUTOR_H
#define EXECUTOR_H
#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>

struct variables
{
    char **ivars_name;
    char **fvars_name;
    int *ivars;
    float *fvars;
};

void print(struct token *list, struct token *list_beg, struct variables *vars);

void myif(struct token *list, struct token *list_beg, struct variables *vars);

void mywhile(struct token *list, struct token *list_beg, struct variables *vars);

void aryth(struct token *list, struct token *list_beg, struct variables *vars);

void read(char *arg1, char *arg2, struct variables *vars, struct token *list_beg);

#endif