/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blax <blax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:25:56 by blax              #+#    #+#             */
/*   Updated: 2023/12/18 09:26:35 by blax             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char* expand_variables(const char *input)
{
    const char *ptr;
    char *result;

    ptr = input;
    result = ft_strdup("");
    while (*ptr)
    {
        if (*ptr == '$' && (ft_isalpha(*(ptr + 1)) || *(ptr + 1) == '?'))
            result = process_dollar_sign(&ptr, result);
        else
            result = process_text_until_next_dollar(&ptr, result);
    }

    return (result);
}

char* process_dollar_sign(const char **ptr, char *result)
{
    char *temp;
    char *varName;

    (*ptr)++; // Passer le symbole '$'
    varName = extract_var_name(ptr);
    temp = append_variable_value(result, varName);
    free(result);
    free(varName);

    return (temp);
}

char* process_text_until_next_dollar(const char **ptr, char *result)
{
    const char *nextDollar;
    char *temp;

    nextDollar = ft_strchr(*(ptr + 1), '$');
    if (!nextDollar) nextDollar = *ptr + ft_strlen(*ptr); // Si pas de '$', aller à la fin
    temp = copy_until_char(result, *ptr, *nextDollar);
    free(result);
    *ptr = nextDollar;

    return (temp);
}