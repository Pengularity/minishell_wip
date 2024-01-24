/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 21:00:04 by wnguyen           #+#    #+#             */
/*   Updated: 2024/01/24 14:48:00 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_env_var(t_env *env)
{
	t_env_link	*current;

	current = env->first;
	while (current != NULL)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(current->name, STDOUT_FILENO);
		ft_putchar_fd('=', STDOUT_FILENO);
		ft_putstr_fd(current->content, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		current = current->next;
	}
}

char	*get_env_content(const char *str)
{
	int		i;
	char	*content;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	content = ft_substr(str, i + 1, ft_strlen(str) - i);
	return (content);
}

void	export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

int	check_env_name(const char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_' && str[i] != '=')
		return (0);
	i++;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '=')
			return (0);
		i++;
	}
	return (1);
}


int	ft_export(t_node *node, t_env *env)
{
	int			i;
	t_env_link	*new_link;

	i = 1;
	if (!node->tab_exec[1] || node->tab_exec[1][0] == '#')
	{
		print_env_var(env);
		return (0);
	}	
	while (node->tab_exec[i] && node->tab_exec[i][0] != '#')
	{
		if (check_env_name(node->tab_exec[i]))
		{
			new_link = env_new_link(node->tab_exec[i]);
			env_connect_links(env->last, new_link);
			env->last = new_link;
			if (env->first == NULL)
				env->first = new_link;
			env->len++;
		}
		else
			export_error(node->tab_exec[i]);
		i++;
	}
	return (0);
}

