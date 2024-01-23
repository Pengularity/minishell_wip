/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:00:02 by blax              #+#    #+#             */
/*   Updated: 2024/01/20 17:16:38 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool is_redirection_token(t_state type)
{
    return (
        (type == T_REDIR_IN)
        || (type == T_REDIR_OUT)
        || (type == T_REDIR_APPEND)
        || (type == T_REDIR_HEREDOC)
    );
}

// int compt_args(t_token *temp_token)
// {
//     int i;

//     i = 0;
//     while (temp_token && temp_token->type_token != T_PIPE
//         && !is_redirection_token(temp_token->type_token))
//     {
//         i++;
//         temp_token = temp_token->next;
//     }
//     return (i);
// }

char **collect_args(t_token **token_ptr)
{
    t_token *token;
    char **args;
    int num_args;
    int i;

    i = 0;
    token = *token_ptr;
    num_args = compt_args(token);
    args = malloc(sizeof(char*) * (num_args + 1));
    if (!args)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    while (i < num_args)
    {
        args[i] = ft_strdup(token->str);
        token = token->next;
        i++;
    }
    args[num_args] = NULL;
    *token_ptr = token;

    return (args);
}

// // Fonction pour convertir le type de token en type de redirection
// t_state token_type_to_redirection_type(t_state type)
// {
//     if (type == T_REDIR_IN)
//         return T_REDIR_IN;
//     else if (type == T_REDIR_OUT)
//         return T_REDIR_OUT;
//     else if (type == T_REDIR_APPEND)
//         return T_REDIR_APPEND;
//     else if (type == T_REDIR_HEREDOC)
//         return T_REDIR_HEREDOC;
//     else
//         return -1;
// }