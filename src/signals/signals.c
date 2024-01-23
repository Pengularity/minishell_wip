/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 10:53:36 by wnguyen           #+#    #+#             */
/*   Updated: 2023/12/18 12:34:52 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_sigint(int signum)
{
	(void)signum;
	g_info.ret = 130;
	ft_putstr_fd("\nminishell> ", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_signal_handlers(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("Cannot set signal handler for SIGINT");
		exit(EXIT_FAILURE);
	}
	signal(SIGQUIT, SIG_IGN);
}

//input = readline("minishell> ");

void	handle_ctrl_d(char *input)
{
	if (input == NULL)
	{
		ft_putstr_fd("exit\n", 1);
		free(input);
		exit(EXIT_SUCCESS);
	}
	else
		free(input);
}
