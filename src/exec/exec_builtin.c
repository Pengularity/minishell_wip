/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:13:03 by wnguyen           #+#    #+#             */
/*   Updated: 2024/01/24 14:55:27 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	verify_and_exec_builtin(t_node *node, t_env *env, int pid)
{
	if (!node || !node->tab_exec || !node->tab_exec[0] || node->type != N_CMD)
		return (ft_putstr_fd("Invalid command\n", STDERR_FILENO),
			exit(EXIT_FAILURE), 1);
	if (ft_strcmp(node->tab_exec[0], "echo") == 0)
		return (ft_echo(node, env));
	// else if (ft_strcmp(node->tab_exec[0], "cd") == 0)
	// 	ft_cd(node, v);
	else if (ft_strcmp(node->tab_exec[0], "pwd") == 0)
		return (ft_pwd(node, env));
	else if (ft_strcmp(node->tab_exec[0], "export") == 0)
		return (ft_export(node, env));
	else if (ft_strcmp(node->tab_exec[0], "unset") == 0)
		return (ft_unset(node, env));
	else if (ft_strcmp(node->tab_exec[0], "env") == 0)
		return (ft_env(node, env));
	else if (ft_strcmp(node->tab_exec[0], "exit") == 0)
		return (ft_exit(node, env));
	else
		return (0);
	if (pid == 0)
		exit(EXIT_SUCCESS);
}


int	exec_builtin(t_node *node, t_env *env)
{
	int	exit_status;
	int	cpy_stdout;

	exit_status = 0;
	if (node->redir_out || node->redir_append)
		cpy_stdout = dup(STDOUT_FILENO);
	exit_status = verify_and_exec_builtin(node, env, 1);
	if (node->redir_out || node->redir_append)
		dup2(cpy_stdout, STDOUT_FILENO);
	return (exit_status);
}
