/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:33:39 by wnguyen           #+#    #+#             */
/*   Updated: 2024/01/23 13:39:55 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "libft.h"
# include "structures.h"
# include <sys/types.h>

enum e_pipe_fd
{
	PIPE_READ,
	PIPE_WRITE,
	PIPE_TEMP_READ
};

enum e_redir_type
{
	REDIRECT_IN,
	REDIRECT_OUT,
};

typedef struct s_exec_info
{
	unsigned int	command_count;
	t_parsed_cmd	*first_command;
	t_parsed_cmd	*last_command;
	pid_t			*child_pids;
	int				redirect_fds[2];
	int				pipe_fds[3];
	int				last_exit_status;
	unsigned int	current_cmd_index;
}		t_exec_info;

#endif