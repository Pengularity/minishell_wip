/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 13:51:49 by wnguyen           #+#    #+#             */
/*   Updated: 2024/01/25 17:16:44 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_oldpwd(t_env *env)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (perror("ft_cd: getcwd error"));
	update_env_var(env, "OLDPWD", oldpwd);
	free(oldpwd);
}

void	update_pwd(t_env *env)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (perror("ft_cd: getcwd error"));
	update_env_var(env, "PWD", pwd);
	free(pwd);
}

int	ft_cd(t_node *node, t_env *env)
{
	char	*path;

	if (node->tab_exec[1])
		path = node->tab_exec[1];
	else
	{
		path = get_env_name(env, "HOME");
		if (!path)
			return (ft_putstr_fd("ft_cd: HOME not set\n", STDERR_FILENO), 1);
	}
	if (strcmp(path, "-") == 0)
	{
		path = get_env_name(env, "OLDPWD");
		if (!path)
			return (ft_putstr_fd("ft_cd: OLDPWD not set\n", STDERR_FILENO), 1);
	}
	update_oldpwd(env);
	if (chdir(path) == -1)
		return (perror("ft_cd: chdir error"), 1);
	update_pwd(env);
	return (0);
}
