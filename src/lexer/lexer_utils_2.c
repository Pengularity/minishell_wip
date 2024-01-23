/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:23:27 by edesaint          #+#    #+#             */
/*   Updated: 2024/01/22 21:49:38 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_token_add_back(t_token **token, t_token *newlist)
{
	t_token	*l;

	if (!token || !newlist)
		return ;
	if (*token)
	{
		l = ft_token_last(*token);
		l->next = newlist;
	}
	else
		*token = newlist;
}

t_token	*ft_token_last(t_token *token)
{
	if (!token)
		return (NULL);
	while (token->next)
		token = token->next;
	return (token);
}

void	ft_token_iter(t_token *token, void (*f)(void *))
{
	while (token)
	{
		f(token->str);
		token = token->next;
	}
}
