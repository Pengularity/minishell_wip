/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:27:15 by blax              #+#    #+#             */
/*   Updated: 2024/01/22 21:05:17 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Fonction pour copier la chaîne jusqu'au caractère délimitateur
char* copy_until_char(char *dest, const char *src, char delimiter)
{
    size_t len_new_result;
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
    len_new_result = len + n + 1;
    newResult = malloc(sizeof(char) * len_new_result);
    ft_strlcpy(newResult, dest, len_new_result);
    ft_strlcat(newResult, src, len_new_result);

    return (newResult);
}

// Fonction pour extraire le nom de la variable
char* extract_var_name(const char **ptr)
{
    const char *start;

    start = *ptr;
    while (ft_isalnum(**ptr) || **ptr == '_')
        (*ptr)++;
    return (ft_strndup(start, *ptr - start));
}

// Fonction pour ajouter la valeur de la variable au résultat
char* append_variable_value(char *result, const char *varName)
{
    char *varValue;
    size_t newLength;
    char *newResult;

    // Gestion spéciale pour le cas "$?"
    if (ft_strcmp(varName, "?") == 0)
    {
        varValue = ft_itoa(g_info); // Vous devez définir cette fonction
        // varValue = ft_itoa(get_last_exit_status()); // Vous devez définir cette fonction
    }
    else
    {
        varValue = getenv(varName);
    }
    if (varValue)
    {
        newLength = ft_strlen(result) + ft_strlen(varValue) + 1;
        newResult = malloc(sizeof(char) * newLength);
        ft_strlcpy(newResult, result, newLength);
        ft_strlcat(newResult, varValue, newLength);
        return (newResult);
    }

    return (ft_strdup(result));
}