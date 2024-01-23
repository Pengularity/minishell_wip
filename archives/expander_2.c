/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blax <blax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 23:04:42 by blax              #+#    #+#             */
/*   Updated: 2023/12/15 09:37:19 by blax             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Fonction principale pour l'expansion des variables
char* expandVariables(const char *input)
{
    const char *ptr;
    char *result;
    char *temp;
    const char *nextDollar;
    char *varName;

    ptr = input;
    result = strdup("");
    while (*ptr)
    {
        if (*ptr == '$' && (isalpha(*(ptr + 1)) || *(ptr + 1) == '?'))
        {
            ptr++; // Passer le symbole '$'
            varName = extractVarName(&ptr);
            temp = appendVariableValue(result, varName);
            free(result);
            result = temp;
            free(varName);
        }
        else
        {
            nextDollar = strchr(ptr, '$');
            if (!nextDollar) nextDollar = ptr + strlen(ptr); // Si pas de '$', aller à la fin
            temp = copyUntilChar(result, ptr, *nextDollar);
            free(result);
            result = temp;
            ptr = nextDollar;
        }
    }

    return (result);
}

// Fonction pour copier la chaîne jusqu'au caractère délimitateur
char* copyUntilChar(char *dest, const char *src, char delimiter)
{
    size_t len;
    size_t n;
    const char *ptr;
    char *newResult;
    
    len = ft_strlen(dest);
    n = 0;
    ptr = src;
    while (*ptr && *ptr != delimiter)
    {
        n++;
        ptr++;
    }
    newResult = malloc(len + n + 1);
    strcpy(newResult, dest);
    strncat(newResult, src, n);

    return (newResult);
}

// Fonction pour extraire le nom de la variable
char* extractVarName(const char **ptr)
{
    const char *start;
    start = *ptr;
    while (isalnum(**ptr) || **ptr == '_')
        (*ptr)++;
    return (strndup(start, *ptr - start));
}

// Fonction pour ajouter la valeur de la variable au résultat
char* appendVariableValue(char *result, const char *varName)
{
    char *varValue;
    size_t newLength;
    char *newResult;

    varValue = getenv(varName);
    if (varValue)
    {
        newLength = strlen(result) + strlen(varValue) + 1;
        newResult = malloc(newLength);
        strcpy(newResult, result);
        strcat(newResult, varValue);
        return newResult;
    }

    return (strdup(result));
}

void expand_tokens(t_data *data)
{
    t_token *current_token;
    char *expanded_value;
    char *command_output;

    current_token = data->token;
    while (current_token != NULL)
    {
        if (current_token->type_str == D_QUOTE)
        {
            expanded_value = expand_variables(current_token->str);
            if (expanded_value)
            {
                replace_token_str(current_token, expanded_value);
                free(expanded_value); // Je ne pense pas qu'il doit etre free
            }
        }
        current_token = current_token->next;
    }
}

void replace_token_str(t_token *token, char *new_value)
{
    free(token->str);
    token->str = strdup(new_value);
}

int main()
{
    const char *input = "ici$USER coucou";
    char *expanded = expandVariables(input);

    printf("Avant l'expansion : %s\n", input);
    printf("Après l'expansion : %s\n", expanded);

    free(expanded);

    return (0);
}