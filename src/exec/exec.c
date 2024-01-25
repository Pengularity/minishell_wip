/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 10:04:08 by blax              #+#    #+#             */
/*   Updated: 2024/01/25 20:50:30 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


void	launch_command(t_node *node)
{
	if (execvp(node->tab_exec[0], node->tab_exec) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(node->tab_exec[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(127);
	}
}

// void	execute_command(t_node *node, int *fd_in, int *fd_out)
// {
// 	pid_t	pid;

// 	if (node->next != NULL)
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("fork");
// 		exit(EXIT_FAILURE);
// 	}
// 	if (pid == 0)
// 	{
// 		// setup_redirections(fd_in, fd_out);
// 		if (strcmp(node->tab_exec[0], "exit") == 0)
// 			exit(atoi(node->tab_exec[1]));
// 		verify_and_exec_builtin(node, NULL, 1);
// 		launch_command(node);
// 	}
// 	else
// 	{
// 		if (fd_in[0] != STDIN_FILENO)
// 			close(fd_in[0]);
// 		if (node->next != NULL)
// 		{
// 			close(fd_out[1]);
// 			fd_in[0] = fd_out[0];
// 		}
// 		waitpid(pid, NULL, 0);
// 	}
// }

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
		if (exec_builtin(node, env))
			exit(EXIT_SUCCESS);
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
		exec_builtin(node, env);
	else if (node->next != NULL)
	{
		envp = convert_env_to_tab(env);
		exec_pipeline(node, envp);
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
