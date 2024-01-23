/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 13:49:07 by wnguyen           #+#    #+#             */
/*   Updated: 2024/01/23 14:27:12 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_env_var(t_env *env, const char *key, const char *value)
{
	t_env_element	*new_var;

	new_var = malloc(sizeof(t_env_element));
	if (!new_var)
		return (perror("malloc error"));
	new_var->key = ft_strdup(key);
	new_var->value = ft_strdup(value);
	new_var->next = NULL;
	new_var->prev = env->last;
	if (env->last)
		env->last->next = new_var;
	else
		env->first = new_var;
	env->last = new_var;
	env->len++;
}

void	update_env_var(t_env *env, const char *key, const char *value)
{
	t_env_element	*current;

	current = env->first;
	while (current)
	{
		if (strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
	add_env_var(env, key, value);
}

char	*get_env_key(t_env *env, const char *key)
{
	t_env_element	*current;

	current = env->first;
	while (current)
	{
		if (strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

char	*get_env_value(t_env *env, const char *value)
{
	int		i;
	char	*key;

	i = 0;
	while (value[i] && value[i] != '=')
		i++;
	key = ft_substr(value, i + 1, ft_strlen(value) - i);
	return (key);
}

char	*get_env_path(t_env *env)
{
	t_env_element	*current;

	current = env->first;
	while (current)
	{
		if (strcmp(current->key, "PATH") == 0)
			return (current->value);
		current = current->next;
	}
}
