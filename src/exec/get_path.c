/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:00:59 by wnguyen           #+#    #+#             */
/*   Updated: 2024/01/23 15:44:45 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/exec.h"

static char	*get_path_env(t_env *env)
{
	t_env_element	*current;

	current = env->first;
	while (current)
	{
		if (ft_strncmp(current->key, "PATH", 4) == 0)
			return (current->value);
		current = current->next;
	}
	ft_putstr_fd("PATH not found in env\n", STDERR_FILENO);
	return (NULL);
}

static char	**split_path(char *path)
{
	char	**paths;

	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

char	**get_full_path(char *const *evnp)
{
	char	*path;
	char	**paths;
	char	*tmp;
	int		i;

	i = 0;
	path = get_path_env(evnp);
	paths = split_path(path);
	if (!paths || !path)
		return (NULL);
	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(tmp, "/");
		if (!paths[i])
		{
			free_tab(paths);
			return (NULL);
		}
		free(tmp);
		i++;
	}
	return (paths);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
