/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 13:49:07 by wnguyen           #+#    #+#             */
/*   Updated: 2024/01/24 16:33:56 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_env_var(t_env *env, const char *name, const char *content)
{
	t_env_link	*new_var;

	new_var = malloc(sizeof(t_env_link));
	if (!new_var)
		return (perror("malloc error"));
	new_var->name = ft_strdup(name);
	new_var->content = ft_strdup(content);
	new_var->next = NULL;
	new_var->prev = env->last;
	if (env->last)
		env->last->next = new_var;
	else
		env->first = new_var;
	env->last = new_var;
	env->len++;
}

void	update_env_var(t_env *env, const char *name, const char *content)
{
	t_env_link	*current;

	current = env->first;
	while (current)
	{
		if (strcmp(current->name, name) == 0)
		{
			free(current->content);
			current->content = ft_strdup(content);
			return ;
		}
		current = current->next;
	}
	add_env_var(env, name, content);
}

char	*get_env_name(t_env *env, const char *name)
{
	t_env_link	*current;

	current = env->first;
	while (current)
	{
		if (strcmp(current->name, name) == 0)
			return (current->content);
		current = current->next;
	}
	return (NULL);
}

char	*join_var_in_str(t_env_link *env_link)
{
	char	*res;
	char	*temp;

	temp = ft_strjoin(env_link->name, "=");
	if (!temp)
		return (NULL);
	res = ft_strjoin(temp, env_link->content);
	free (temp);
	if (!res)
		return (NULL);
	return (res);
}

char	**convert_env_to_tab(t_env *env)
{
	unsigned int	i;
	char			**res;
	t_env_link		*env_link;

	i = 0;
	res = (char **)malloc(sizeof(char *) * (env->len + 1));
	if (!res)
		return (NULL);
	env_link = env->first;
	while (i < env->len)
	{
		res[i] = join_var_in_str(env_link);
		if (!res[i])
			return (res); // a free
		env_link = env_link->next;
		i++;
	}
	res[i] = 0;
	return (res);
}
