/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:04:50 by wnguyen           #+#    #+#             */
/*   Updated: 2024/01/26 15:39:37 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	create_pipe_and_fork(int *pipe_fds)
{
	int	pid;

	if (pipe(pipe_fds) == -1)
		return (perror("pipe error"), -1);
	pid = fork();
	if (pid == -1)
		return (perror("fork error"), -1);
	if (pid == 0)
	{
		close(pipe_fds[0]);
		if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
			return (perror("dup2"), -1);
		close(pipe_fds[1]);
	}
	if (pid != 0)
		close(pipe_fds[1]);
	return (pid);
}

void	execute_pipe_command(t_node *node, int in_fd, char **envp, t_env *env)
{
	if (in_fd != STDIN_FILENO)
	{
		if (dup2(in_fd, STDIN_FILENO) == -1)
			return (perror("dup2"), exit(EXIT_FAILURE));
		close(in_fd);
	}
	if (is_builtin(node))
		exit(exec_builtin(node, env));
	execute_command(node, envp);
	exit(EXIT_SUCCESS);
}

void	exec_pipeline_rec(t_node *node, int in_fd, char **envp, t_env *env)
{
	int		pipe_fds[2];
	int		pid;

	if (node->next)
	{
		pid = create_pipe_and_fork(pipe_fds);
		if (pid == -1)
			return ;
		if (pid == 0)
			execute_pipe_command(node->next, in_fd, envp, env);
		close(pipe_fds[1]);
		if (in_fd != STDIN_FILENO)
			close(in_fd);
		// waitpid(pid, NULL, 0);
		exec_pipeline_rec(node->next, pipe_fds[0], envp, env);
		close(pipe_fds[0]);
		// waitpid(pid, NULL, 0);
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (in_fd != STDIN_FILENO)
				dup2(in_fd, STDIN_FILENO);
			execute_pipe_command(node, in_fd, envp, env);
			exit(EXIT_SUCCESS);
		}
		if (in_fd != STDIN_FILENO)
			close(in_fd);
		waitpid(pid, NULL, 0);
	}
}

void	exec_pipeline(t_node *node, char **envp, t_env *env)
{
	exec_pipeline_rec(node, STDIN_FILENO, envp, env);
}

