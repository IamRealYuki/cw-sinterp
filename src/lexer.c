#include "lexer.h"
void delete_spaces(char *arr)
{
    while (1)
    {
        if (arr[0] == ' ')
        {
            int i = 0;
            while (arr[i] != '\n')
            {
                arr[i] = arr[i + 1];
                i++;
            }
        }
        else
            return;
    }
}

void deleten(char *arr, int n)
{
    int i = 0;
    while (arr[i + n] != '\n')
    {
        arr[i] = arr[i + n];
        i++;
    }
    arr[i] = arr[i + n];
}

void lexemize(char *name_of_file, struct token *list)
{
    FILE *file = fopen(name_of_file, "r");
    char *string = (char *)malloc(100 * sizeof(char));

    while (!feof(file))
    {
        int j = 0;
        fgets(string, 100, file);
        list->next = (struct token *)malloc(sizeof(struct token));
        list->tokens = (char **)malloc(sizeof(char *) * 6);
        for (int i = 0; i < 6; i++)
        {
            list->tokens[i] = (char *)malloc(sizeof(char) * 10);
        }
        while (string[0] != '\n')
        {
            delete_spaces(string);
            int count = 0;
            int i = 0;
            while (string[i] != ' ')
            {
                if (string[i] == '\n')
                    break;
                count++;
                i++;
            }
            strncpy(list->tokens[j], string, count);
            deleten(string, count);
            j++;
        }
        strcpy(list->tokens[j], "lastarg");
        list = list->next;
    }
    list = NULL;
    free(string);
}