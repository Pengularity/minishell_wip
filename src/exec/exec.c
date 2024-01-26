/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 10:04:08 by blax              #+#    #+#             */
/*   Updated: 2024/01/26 17:39:48 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_single_cmd(t_node *node, t_env *env)
{
	pid_t	pid;
	int		status;
	char	**envp;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		envp = convert_env_to_tab(env);
		execute_command(node, envp);
		free(envp);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_info = WEXITSTATUS(status);
	}
}

void	execute_command_node(t_node *node, t_env *env)
{
	char	**envp;

	if (!node || !node->tab_exec || !node->tab_exec[0] || node->type != N_CMD)
		return (ft_putstr_fd("Invalid command\n", STDERR_FILENO),
			exit(EXIT_FAILURE));
	if (node->id == 0 && node->next == NULL && is_builtin(node))
	{
		if (node->tab_exec[0] && ft_strcmp(node->tab_exec[0], "exit") == 0)
			ft_putendl_fd("exit", STDOUT_FILENO);
		exec_builtin(node, env);
	}
	else if (node->next != NULL)
	{
		envp = convert_env_to_tab(env);
		exec_pipeline(node, env);
		free(envp);
	}
	else
		execute_single_cmd(node, env);
}

// {
// 	pid_t	pid;
// 	int		status;
// 	char	**envp;

// 	if (!node || !node->tab_exec || !node->tab_exec[0] || node->type != N_CMD)
// 		return (ft_putstr_fd("Invalid command\n", STDERR_FILENO),
// 			exit(EXIT_FAILURE));
// 	if (node->id == 0 && node->next == NULL && is_builtin(node))
// 		exec_builtin(node, env);
// 	else
// 	{
// 		pid = fork();
// 		if (pid == -1)
// 		{
// 			perror("fork");
// 			exit(EXIT_FAILURE);
// 		}
// 		if (pid == 0)
// 		{
// 			exec_builtin(node, env);
// 			envp = convert_env_to_tab(env);
// 			execute_command(node, envp);
// 			free(envp);
// 			exit(EXIT_SUCCESS);
// 		}
// 		else
// 		{
// 			waitpid(pid, &status, 0);
// 			if (WIFEXITED(status))
// 				g_info = WEXITSTATUS(status);
// 		}
// 	}
// }

void	start_execute(t_node *node);

//s'assurer de bien initialiser fd_in[0] a STDIN_FILENO
