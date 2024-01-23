/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 21:31:23 by wnguyen           #+#    #+#             */
/*   Updated: 2024/01/21 17:33:22 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Check if the input string is the '-n' option.
 * Returns true if it matches, false otherwise.
 */

bool	is_n_option(char *str)
{
	int	i;

	if (str[0] != '-' || str[1] != 'n')
		return (false);
	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

/*
 * Custom implementation of the 'echo' command.
 * Outputs the given arguments to the standard output.
 * Supports the '-n' option to suppress the trailing newline.
 */

void	ft_echo(t_node *node, t_env *env)
{
	int	i;
	int	n_option;

	(void)env;
	i = 1;
	n_option = 0;
	if (!node->tab_exec[1])
		return (ft_putchar_fd('\n', STDOUT_FILENO));
	while (node->tab_exec[i] && is_n_option(node->tab_exec[i]))
	{
		n_option = 1;
		i++;
	}
	while (node->tab_exec[i])
	{
		ft_putstr_fd(node->tab_exec[i], STDOUT_FILENO);
		if (node->tab_exec[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (!n_option)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

// int main() {
//     // Test 1: L'option -n valide
//     char *test1[] = {"echo", "-n", "-n", "Hello, World!", NULL};
//     ft_echo(test1);

//     // Test 2: L'option -n suivie de caractères non 'n'
//     char *test2[] = {"echo", "-nx", "Hello, World!", NULL};
//     ft_echo(test2);

//     // Test 3: Aucune option -n
//     char *test3[] = {"echo", "Hello, World!", NULL};
//     ft_echo(test3);

//     // Test 4: Mélange de -n valide et d'autres arguments
//     char *test4[] = {"echo", "-n", "-nnn", "-nx", "message", NULL};
//     ft_echo(test4);

//     // Test 5: L'option -n avec des espaces avant le message
//     char *test5[] = {"echo", "-n", "     ", "Hello, World!", NULL};
//     ft_echo(test5);

//     return 0;
// }
