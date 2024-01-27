/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:15:34 by wnguyen           #+#    #+#             */
/*   Updated: 2024/01/27 16:19:36 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	redir_in(t_node *node)
{
	int	fd_in;

	fd_in = open(node->redir_in, O_RDONLY);
	if (fd_in < 0)
		return (perror("open"), EXIT_FAILURE);
	if (dup2(fd_in, STDIN_FILENO) < 0)
	{
		close(fd_in);
		return (perror("dup2"), EXIT_FAILURE);
	}
	close(fd_in);
	return (EXIT_SUCCESS);
}

static int	redir_out(t_node *node)
{
	int	fd_out;

	fd_out = open(node->redir_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out < 0)
		return (perror("open"), EXIT_FAILURE);
	if (dup2(fd_out, STDOUT_FILENO) < 0)
	{
		close(fd_out);
		return (perror("dup2"), EXIT_FAILURE);
	}
	close(fd_out);
	return (EXIT_SUCCESS);
}

static int	redir_append(t_node *node)
{
	int	fd_append;

	fd_append = open(node->redir_append, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_append < 0)
		return (perror("open"), EXIT_FAILURE);
	if (dup2(fd_append, STDOUT_FILENO) < 0)
	{
		close(fd_append);
		return (perror("dup2"), EXIT_FAILURE);
	}
	close(fd_append);
	return (EXIT_SUCCESS);
}

static int	redir_heredoc(t_node *node)
{
	int	fd_heredoc;

	fd_heredoc = open(node->redir_heredoc, O_RDONLY);
	if (fd_heredoc < 0)
		return (perror("open"), EXIT_FAILURE);
	if (dup2(fd_heredoc, STDIN_FILENO) < 0)
	{
		close(fd_heredoc);
		return (perror("dup2"), EXIT_FAILURE);
	}
	close(fd_heredoc);
	return (EXIT_SUCCESS);
}

int	exec_redir(t_node *node)
{
	if (node->redir_in && ft_strlen(node->redir_in))
	{
		if (redir_in(node))
			return (EXIT_FAILURE);
	}
	else if (node->redir_out && ft_strlen(node->redir_out))
	{
		if (redir_out(node))
			return (EXIT_FAILURE);
	}
	else if (node->redir_append && ft_strlen(node->redir_append))
	{
		if (redir_append(node))
			return (EXIT_FAILURE);
	}
	else if (node->redir_heredoc && ft_strlen(node->redir_heredoc))
	{
		if (redir_heredoc(node))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
