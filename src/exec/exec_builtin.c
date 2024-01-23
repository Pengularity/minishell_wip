/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:31:46 by wnguyen           #+#    #+#             */
/*   Updated: 2024/01/23 14:28:50 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/exec.h"

int	exec_builtin(t_node *node, t_env *env)
{
	if (ft_strcmp(node->tab_exec[0], "echo") == 0)
		ft_echo(node, env);
	else if (ft_strcmp(node->tab_exec[0], "cd") == 0)
		ft_cd(node, env);
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
		return (0);
	return (1);
}

int	builtin_main(t_exec_info *exec_info, t_env *env)
{
	int 			exit_status;
	t_parsed_cmd	*cmd_list;
	int				cpy_stdout;

	exit_status = 0;
	cmd_list = exec_info->first_command;

}