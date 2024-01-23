/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:15:34 by wnguyen           #+#    #+#             */
/*   Updated: 2024/01/22 17:51:32 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	redir_in(t_node *node)
{
	int	fd;

	fd = open(node->redir_in, O_RDONLY);
	if (fd < 0)
		return (perror("open"), EXIT_FAILURE);
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		close(fd);
		return (perror("dup2"), EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

static int	redir_out(t_node *node)
{
	int	fd;

	fd = open(node->redir_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (perror("open"), EXIT_FAILURE);
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		close(fd);
		return (perror("dup2"), EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

static int	redir_append(t_node *node)
{
	int	fd;

	fd = open(node->redir_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (perror("open"), EXIT_FAILURE);
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		close(fd);
		return (perror("dup2"), EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

static int	redir_heredoc(t_node *node)
{
	int	fd;

	fd = open(node->redir_heredoc, O_RDONLY);
	if (fd < 0)
		return (perror("open"), EXIT_FAILURE);
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		close(fd);
		return (perror("dup2"), EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}
