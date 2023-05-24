#include <stdbool.h>
#include "executor.h"
#include "clean.h"

int idenf(char *thing, struct variables *vars)
{
    for (int i = 0; i < 20; i++)
    {
        if (strcmp(thing, vars->ivars_name[i]) == 0)
            return 1;
    }
    for (int i = 0; i < 20; i++)
    {
        if (strcmp(thing, vars->fvars_name[i]) == 0)
            return 2;
    }
    int point = 0;
    char numbers[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    for (int i = 0; thing[i] != '\000'; i++)
    {
        if (strchr(numbers, thing[i]) == NULL)
        {
            if (thing[i] == '-' && i != 0)
            {
                printf("Neither variable of number\n");
                return -1;
            }
            if (thing[i] == '.' && i == 0)
            {
                printf("Neither variable of number\n");
                return -1;
            }
            if (thing[i] == '.')
                point++;

            if (point > 1)
            {
                printf("Neither variable of number\n");
                return -1;
            }
        }
    }
    if (point == 0)
        return 1;
    return 2;
}

int get_val_i(char *arg, struct variables *vars)
{
    for (int i = 0; i < 20; i++)
    {
        if (strcmp(arg, vars->ivars_name[i]) == 0)
            return vars->ivars[i];
    }
    return atoi(arg);
}

float get_val_f(char *arg, struct variables *vars)
{
    for (int i = 0; i < 20; i++)
    {
        if (strcmp(arg, vars->fvars_name[i]) == 0)
            return vars->fvars[i];
    }
    return atof(arg);
}

int findi(char *vars_name, struct variables *vars)
{
    for (int i = 0; i < 20; i++)
    {
        if (strcmp(vars_name, vars->ivars_name[i]) == 0)
            return i;
        if (strcmp(vars->ivars_name[i], "0") == 0)
            return i;
    }
    return 19;
}
int findf(char *vars_name, struct variables *vars)
{
    for (int i = 0; i < 20; i++)
    {
        if (strcmp(vars_name, vars->fvars_name[i]) == 0)
            return i;
        if (strcmp(vars->fvars_name[i], "0") == 0)
            return i;
    }
    return 19;
}

int cont(struct token *list, struct token *list_beg, struct variables *vars)
{
    int operator= 0;
    bool ifcont = 0;
    if (strcmp(list->tokens[2], "!=") == 0)
        operator= 1;
    else if (strcmp(list->tokens[2], "==") == 0)
        operator= 2;
    else if (strcmp(list->tokens[2], "<") == 0)
        operator= 3;
    else if (strcmp(list->tokens[2], ">") == 0)
        operator= 4;
    if (operator== 0)
    {
        printf("Incorrect operation");
        delete_vars(vars);
        clean(list_beg);
        exit(1);
    }
    int type_arg_1 = idenf(list->tokens[1], vars);
    int type_arg_3 = idenf(list->tokens[3], vars);
    if (type_arg_1 == -1 || type_arg_3 == -1)
    {
        delete_vars(vars);
        clean(list_beg);
        exit(1);
    }
    if (type_arg_1 != type_arg_3)
    {
        printf("Arguments must have same type");
        delete_vars(vars);
        clean(list_beg);
        exit(1);
    }
    else if (type_arg_1 == 1)
    {
        int arg_1_val = get_val_i(list->tokens[1], vars);
        int arg_3_val = get_val_i(list->tokens[3], vars);
        switch (operator)
        {
        case 1:
            if (arg_1_val != arg_3_val)
                ifcont = 1;
            break;
        case 2:
            if (arg_1_val == arg_3_val)
                ifcont = 1;
            break;
        case 3:
            if (arg_1_val < arg_3_val)
                ifcont = 1;
            break;
        case 4:
            if (arg_1_val > arg_3_val)
                ifcont = 1;
            break;
        }
    }
    else
    {
        float arg_1_val = get_val_f(list->tokens[1], vars);
        float arg_3_val = get_val_f(list->tokens[3], vars);
        switch (operator)
        {
        case 1:
            if (arg_1_val != arg_3_val)
                ifcont = 1;
            break;
        case 2:
            if (arg_1_val == arg_3_val)
                ifcont = 1;
            break;
        case 3:
            if (arg_1_val < arg_3_val)
                ifcont = 1;
            break;
        case 4:
            if (arg_1_val > arg_3_val)
                ifcont = 1;
            break;
        }
    }
    return ifcont;
}

void myif(struct token *list, struct token *list_beg, struct variables *vars)
{

    if (cont(list, list_beg, vars) == 0)
    {
        int enclosure = 0;
        while (strcmp(list->tokens[0], "else") != 0)
        {
            if (list->next == NULL)
            {
                printf("endless construction body!");
                delete_vars(vars);
                clean(list_beg);
                exit(1);
            }
            if (strcmp(list->tokens[0], "if") == 0)
                enclosure++;
            if ((strcmp(list->tokens[0], "fi") == 0) && enclosure > 0)
                enclosure--;
            if ((strcmp(list->tokens[0], "fi") == 0) && enclosure == 0)
                return;
            list = list->next;
        }
    }
    list = list->next;
    while (strcmp(list->tokens[0], "fi") != 0 && strcmp(list->tokens[0], "else") != 0)
    {
        if (strcmp(list->tokens[0], "read") == 0)
            read(list->tokens[1], list->tokens[2], vars, list_beg);
        else if (strcmp(list->tokens[0], "print") == 0)
            print(list, list_beg, vars);
        else if (strcmp(list->tokens[0], "while") == 0)
            mywhile(list, list_beg, vars);
        else if (strcmp(list->tokens[0], "if") == 0)
        {
            myif(list, list_beg, vars);
            while (strcmp(list->tokens[0], "fi") != 0)
            {
                list = list->next;
            }
        }
        else
            aryth(list, list_beg, vars);

        if (list->next == NULL)
        {
            delete_vars(vars);
            clean(list_beg);
            exit(1);
        }
        list = list->next;
    }
}

void read(char *arg1, char *arg2, struct variables *vars, struct token *list_beg)
{
    int i = 0;
    if (strcmp(arg1, "-i") == 0)
    {
        i = findi(arg2, vars);
        strcpy(vars->ivars_name[i], arg2);
        printf("Введите значение переменной %s...", arg2);
        while (scanf("%d", &vars->ivars[i]) != 1)
        {
            printf("Incorrect number\n");
            while (getchar() != '\n')
                ;
        }
    }
    else if (strcmp(arg1, "-f") == 0)
    {
        i = findf(arg2, vars);
        strcpy(vars->fvars_name[i], arg2);
        printf("Введите значение переменной %s...", arg2);
        while (scanf("%f", &vars->fvars[i]) != 1)
        {
            printf("Incorrect number\n");
            while (getchar() != '\n')
                ;
        }
    }
    else
    {
        (printf("Expected var type\n"));
        {
            delete_vars(vars);
            clean(list_beg);
            exit(1);
        }
    }
}

void mywhile(struct token *list, struct token *list_beg, struct variables *vars)
{
    struct token *holder = list;
    while (1)
    {
        if (cont(list, list_beg, vars) == 0)
            break;
        list = list->next;
        while (strcmp(list->tokens[0], "done") != 0)
        {
            if (strcmp(list->tokens[0], "read") == 0)
                read(list->tokens[1], list->tokens[2], vars, list_beg);
            else if (strcmp(list->tokens[0], "print") == 0)
                print(list, list_beg, vars);
            else if (strcmp(list->tokens[0], "if") == 0)
            {
                myif(list, list_beg, vars);
                while (strcmp(list->tokens[0], "fi") != 0)
                {
                    list = list->next;
                }
            }
            else if (strcmp(list->tokens[0], "while") == 0)
            {
                mywhile(list, list_beg, vars);
                while (strcmp(list->tokens[0], "done") != 0)
                {
                    list = list->next;
                }
            }
            else
                aryth(list, list_beg, vars);
            if (list->next == NULL)
            {
                delete_vars(vars);
                clean(list_beg);
                exit(1);
            }
            list = list->next;
        }
        list = holder;
    }
}

void aryth(struct token *list, struct token *list_beg, struct variables *vars)
{
    if (strcmp(list->tokens[1], "=") != 0)
    {
        delete_vars(vars);
        clean(list_beg);
        exit(1);
    }

    int type_arg_2 = idenf(list->tokens[2], vars);
    int type_arg_4 = idenf(list->tokens[4], vars);
    if (type_arg_2 == -1 || type_arg_4 == -1)
    {
        delete_vars(vars);
        clean(list_beg);
        exit(1);
    }
    int operator;
    if (type_arg_2 != type_arg_4)
    {
        printf("Arguments must have same type");
        delete_vars(vars);
        clean(list_beg);
        exit(1);
    }
    if (strcmp(list->tokens[3], "+") == 0)
        operator= 1;
    else if (strcmp(list->tokens[3], "-") == 0)
        operator= 2;
    else if (strcmp(list->tokens[3], "*") == 0)
        operator= 3;
    else if (strcmp(list->tokens[3], "\\") == 0)
        operator= 4;
    else if (strcmp(list->tokens[3], "lastarg") == 0)
        operator= 5;
    if (operator== 0)
    {
        printf("Incorrect operation");
        delete_vars(vars);
        clean(list_beg);
        exit(1);
    }
    if (type_arg_2 == 1)
    {
        switch (operator)
        {
        case 1:
            vars->ivars[findi(list->tokens[0], vars)] = get_val_i(list->tokens[2], vars) + get_val_i(list->tokens[4], vars);
            strcpy(vars->ivars_name[findi(list->tokens[0], vars)], list->tokens[0]);
            break;
        case 2:
            vars->ivars[findi(list->tokens[0], vars)] = get_val_i(list->tokens[2], vars) - get_val_i(list->tokens[4], vars);
            strcpy(vars->ivars_name[findi(list->tokens[0], vars)], list->tokens[0]);
            break;
        case 3:
            vars->ivars[findi(list->tokens[0], vars)] = get_val_i(list->tokens[2], vars) * get_val_i(list->tokens[4], vars);
            strcpy(vars->ivars_name[findi(list->tokens[0], vars)], list->tokens[0]);
            break;
        case 4:
            vars->ivars[findi(list->tokens[0], vars)] = get_val_i(list->tokens[2], vars) / get_val_i(list->tokens[4], vars);
            strcpy(vars->ivars_name[findi(list->tokens[0], vars)], list->tokens[0]);
            break;
        case 5:
            vars->ivars[findi(list->tokens[0], vars)] = get_val_i(list->tokens[2], vars);
            break;
        }
    }
    if (type_arg_2 == 2)
    {
        switch (operator)
        {
        case 1:
            vars->ivars[findf(list->tokens[0], vars)] = get_val_f(list->tokens[2], vars) + get_val_f(list->tokens[4], vars);
            strcpy(vars->ivars_name[findf(list->tokens[0], vars)], list->tokens[0]);
            break;
        case 2:
            vars->ivars[findf(list->tokens[0], vars)] = get_val_f(list->tokens[2], vars) - get_val_f(list->tokens[4], vars);
            strcpy(vars->ivars_name[findf(list->tokens[0], vars)], list->tokens[0]);
            break;
        case 3:
            vars->ivars[findf(list->tokens[0], vars)] = get_val_f(list->tokens[2], vars) * get_val_f(list->tokens[4], vars);
            strcpy(vars->ivars_name[findf(list->tokens[0], vars)], list->tokens[0]);
            break;
        case 4:
            vars->ivars[findf(list->tokens[0], vars)] = get_val_f(list->tokens[2], vars) / get_val_f(list->tokens[4], vars);
            strcpy(vars->ivars_name[findf(list->tokens[0], vars)], list->tokens[0]);
            break;
        case 5:
            vars->ivars[findf(list->tokens[0], vars)] = get_val_f(list->tokens[2], vars);
        }
    }
}

void print(struct token *list, struct token *list_beg, struct variables *vars)
{
    if (idenf(list->tokens[1], vars) == 1)
        printf("\nПеременная %s: %d\n", list->tokens[1], get_val_i(list->tokens[1], vars));
    else if (idenf(list->tokens[1], vars) == 2)
        printf("\nПеременная %s: %f\n", list->tokens[1], get_val_f(list->tokens[1], vars));
    else
    {
        printf("Can not print");
        delete_vars(vars);
        clean(list_beg);
        exit(1);
    }
}