/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 10:04:08 by blax              #+#    #+#             */
/*   Updated: 2024/01/23 21:28:35 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	verify_and_exec_builtin(t_node *node, t_env *env, int pid)
{
	if (!node || !node->tab_exec || !node->tab_exec[0] || node->type != N_CMD)
		return (ft_putstr_fd("Invalid command\n", STDERR_FILENO),
			exit(EXIT_FAILURE));
	if (ft_strcmp(node->tab_exec[0], "echo") == 0)
		ft_echo(node, env);
	// else if (ft_strcmp(node->tab_exec[0], "cd") == 0)
	// 	ft_cd(node, v);
	else if (ft_strcmp(node->tab_exec[0], "pwd") == 0)
		ft_pwd(node, env);
	else if (ft_strcmp(node->tab_exec[0], "export") == 0)
		ft_export(node, env);
	else if (ft_strcmp(node->tab_exec[0], "unset") == 0)
		ft_unset(node, env);
	else if (ft_strcmp(node->tab_exec[0], "env") == 0)
		ft_env(node, env);
	else if (ft_strcmp(node->tab_exec[0], "exit") == 0)
		ft_exit(node, env);
	else
		return ;
	if (pid == 0)
		exit(EXIT_SUCCESS);
}

// void	setup_redirections(int *fd_in, int *fd_out)
// {
// 	// t_node	*node;

// 	if (fd_in[0] != STDIN_FILENO)
// 	{
// 		if (dup2(fd_in[0], STDIN_FILENO) == -1)
// 			(perror("dup2"), exit(EXIT_FAILURE));
// 		close(fd_in[0]);
// 	}
// 	// if (node->next != NULL)
// 	// {
// 	// 	close(fd_out[0]);
// 	// 	if (dup2(fd_out[1], STDOUT_FILENO) == -1)
// 	// 		(perror("dup2"), exit(EXIT_FAILURE));
// 	// 	close(fd_out[1]);
// 	// }
// }

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

void	execute_command(t_node *node, int *fd_in, int *fd_out)
{
	pid_t	pid;

	if (node->next != NULL)
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		// setup_redirections(fd_in, fd_out);
		if (strcmp(node->tab_exec[0], "exit") == 0)
			exit(atoi(node->tab_exec[1]));
		verify_and_exec_builtin(node, NULL, 1);
		launch_command(node);
	}
	else
	{
		if (fd_in[0] != STDIN_FILENO)
			close(fd_in[0]);
		if (node->next != NULL)
		{
			close(fd_out[1]);
			fd_in[0] = fd_out[0];
		}
		waitpid(pid, NULL, 0);
	}
}

void	execute_command_node(t_node *node, t_env *env)
{
	if (node->id == 0 && node->next == NULL)
		verify_and_exec_builtin(node, env, 1);
	else
	{
		int	fd_in[2];
		int	fd_out[2];

		fd_in[0] = STDIN_FILENO;
		fd_in[1] = STDOUT_FILENO;
		fd_out[0] = STDIN_FILENO;
		fd_out[1] = STDOUT_FILENO;
		while (node != NULL)
		{
			if (node->next != NULL)
				pipe(fd_out);
			verify_and_exec_builtin(node, env, 0);
			execute_command(node, fd_in, fd_out);
			if (node->next != NULL)
			{
				close(fd_out[1]);
				if (fd_in[0] != STDIN_FILENO)
					close(fd_in[0]);
				fd_in[0] = fd_out[0];
			}
			node = node->next;
		}
	}

	// int	fd_out[2];

	// if (!is_last && pipe(fd_out) == -1)
	// {
	// 	perror("pipe");
	// 	exit(EXIT_FAILURE);
	// }
	// verify_and_exec_builtin(node, env, 1);
	// execute_command(node, fd_in, fd_out);
	// if (!is_last)
	// {
	// 	close(fd_out[0]);
	// 	if (fd_in[0] != STDIN_FILENO)
	// 		close(fd_in[0]);
	// }
	// fd_in[0] = fd_out[0];
}

void	start_execute(t_node *node);

//s'assurer de bien initialiser fd_in[0] a STDIN_FILENO
