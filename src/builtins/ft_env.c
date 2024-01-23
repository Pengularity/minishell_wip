/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letnitan <letnitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 07:33:34 by wnguyen           #+#    #+#             */
/*   Updated: 2024/01/23 17:36:11 by letnitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_env(t_node *node, t_env *env)
{
	t_env_link	*current;

	(void)node;
	current = env->first;
	while (current != NULL)
	{
		ft_putstr_fd(current->name, STDOUT_FILENO);
		ft_putchar_fd('=', STDOUT_FILENO);
		ft_putstr_fd(current->content, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		current = current->next;
	}
	printf("\nENV->LAST : %s\n", env->last->name);
	printf("\nENV->LAST->PREV : %s\n", env->last->prev->name);
}
