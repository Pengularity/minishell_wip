/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 21:00:04 by wnguyen           #+#    #+#             */
/*   Updated: 2024/01/23 14:28:07 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_env_var(t_env *env)
{
	t_env_element	*current;

	current = env->first;
	while (current)
	{
		ft_putstr_fd(current->key, STDOUT_FILENO);
		ft_putchar_fd('=', STDOUT_FILENO);
		ft_putstr_fd(current->value, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		current = current->next;
	}
}

void	ft_export(t_node *node, t_env *env)
{
	int			i;
	char		*key;
	char		*value;

	i = 1;
	if (!node->tab_exec[1])
		print_env_var(env);
	while (node->tab_exec[i])
	{
		if (is_valid_env_key(node->tab_exec[i]))
		{
			key = get_env_key(node->tab_exec[i]);
			value = get_env_value(node->tab_exec[i]);
			update_env_var(env, key, value);
			free(key);
			free(value);
		}
		else
			unset_error(node->tab_exec[i]);
		i++;
	}
}
