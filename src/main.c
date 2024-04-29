#include <lexer.h>
#include <executor.h>
#include <clean.h>

void init(struct variables *vars)
{
    vars->ivars_name = (char **)malloc(20 * sizeof(char *));
    vars->ivars = (int *)calloc(20, sizeof(int));
    vars->fvars_name = (char **)malloc(20 * sizeof(char *));
    vars->fvars = (float *)calloc(20, sizeof(float));
    for (int i = 0; i < 20; i++)
    {
        vars->fvars_name[i] = (char *)malloc(10 * sizeof(char));
        vars->ivars_name[i] = (char *)malloc(10 * sizeof(char));
    }
    for (int i = 0; i < 20; i++)
    {
        strcpy(vars->fvars_name[i], "0");
        strcpy(vars->ivars_name[i], "0");
    }
}

int main(int argc, char **argv)
{
    struct token *list = (struct token *)malloc(sizeof(struct token));
    struct token *list_beg = list;
    struct variables *vars = (struct variables *)malloc(sizeof(struct variables));
    init(vars);
    lexemize("print.txt", list);
    int enclosure = 0;
    while (list->next != NULL)
    {
        if (strcmp(list->tokens[0], "read") == 0)
            read(list->tokens[1], list->tokens[2], vars, list_beg);
        else if (strcmp(list->tokens[0], "print") == 0)
            print(list, list_beg, vars);
        else if (strcmp(list->tokens[0], "if") == 0)
        {
            myif(list, list_beg, vars);
            while (strcmp(list->tokens[0], "fi") != 0 || enclosure != 0)
            {
                list = list->next;
                if (strcmp(list->tokens[0], "if") == 0)
                    enclosure++;
                if (strcmp(list->tokens[0], "fi") == 0)
                    enclosure--;
                if (list->next == NULL)
                {
                    delete_vars(vars);
                    clean(list_beg);
                    exit(1);
                }
            }
        }
        else if (strcmp(list->tokens[0], "while") == 0)
        {
            mywhile(list, list_beg, vars);
            while (strcmp(list->tokens[0], "done") != 0)
            {
                list = list->next;
                if (list->next == NULL)
                {
                    delete_vars(vars);
                    clean(list_beg);
                    exit(1);
                }
            }
        }
        else
            aryth(list, list_beg, vars);
        list = list->next;
    }
    delete_vars(vars);
    clean(list_beg);
    return 0;
}