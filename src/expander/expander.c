/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 23:04:42 by blax              #+#    #+#             */
/*   Updated: 2024/01/22 21:00:06 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int g_last_exit_status = 0;

// // Fonction pour obtenir le dernier statut de sortie
// int get_last_exit_status(void)
// {
//     // Supposons que vous avez une variable globale ou une structure qui stocke cette information
//     return (g_last_exit_status); // Remplacez par votre propre mécanisme de stockage
// }

bool is_expandable(t_token *token)
{
    if (!token)
        return (NULL);
    return (token->type_str == D_QUOTE || token->type_str == S_CHAR);
}

void expand_tokens(t_data *data)
{
    t_token *cur_token;
    char *expanded_value;

    cur_token = data->token;
    while (cur_token)
    {
        if (is_expandable(cur_token))
        {
            expanded_value = expand_variables(cur_token->str);
            if (expanded_value)
            {
                replace_token_str(cur_token, expanded_value);
                free(expanded_value); // Je ne pense pas qu'il doit etre free
            }
        }
        if (cur_token)
            cur_token = cur_token->next;
    }
}

void replace_token_str(t_token *token, char *new_value)
{
    free(token->str);
    token->str = ft_strdup(new_value);
}

// void print_expanded_tokens(t_token *tokens)
// {
//     while (tokens != NULL)
// 	{
//         if (is_empty_token(tokens))
//             printf("%s", tokens->str);
//         else
//             printf(" %s", tokens->str);
//         tokens = tokens->next;
//     }
// }