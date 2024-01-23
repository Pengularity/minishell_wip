/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 22:31:24 by edesaint          #+#    #+#             */
/*   Updated: 2024/01/22 22:31:46 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void free_tab_exec(char **tab_exec)
{
    // int i;

    if (!tab_exec)
        return ;
    // i = 0;
    // while (tab_exec[i])
	// {
	// 	free(tab_exec[i]);
	// 	tab_exec[i] = NULL;
    //     i++;
	// }
	free(tab_exec);
    tab_exec = NULL;
}

void free_nodes(t_node *node)
{
    t_node *tmp_node;

    while (node)
    {
        tmp_node = node;
        node = node->next;
        free_tab_exec(tmp_node->tab_exec);
        free(tmp_node);
        tmp_node = NULL;
    }
}

void	ft_free_tab(char **s, int i)
{
	while (i-- > 0)
	{
		if (s[i])
		{
			free(s[i]);
			s[i] = NULL;
		}
	}
	free(s);
}

void free_tokens(t_token *token)
{
    t_token *tmp_token;

    while (token)
    {
        tmp_token = token->next;
        if (token->str)
        {
            free(token->str);
            token->str = NULL;
        }
        free(token);
        token = tmp_token;
    }
}

void free_data(t_data *data)
{
    if (data->str)
    {
        free(data->str);
        data->str = NULL;
    }
}
