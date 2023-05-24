#include <stdio.h>

#include "lexer.h"
#include "executor.h"

void clean(struct token *list)
{
    for (int i = 0; i < 6; i++)
        free(list->tokens[i]);
    free(list->tokens);
    if (list->next->next != NULL)
        clean(list->next);
    else
    {
        free(list->next->tokens);
        free(list->next);
    }
    free(list);
}
void delete_vars(struct variables *vars)
{
    for (int i = 0; i < 20; i++)
    {
        free(vars->fvars_name[i]);
        free(vars->ivars_name[i]);
    }
    free(vars->fvars_name);
    free(vars->ivars_name);
    free(vars->ivars);
    free(vars->fvars);
    free(vars);
}