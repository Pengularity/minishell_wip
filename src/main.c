/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letnitan <letnitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:23:51 by blax              #+#    #+#             */
/*   Updated: 2024/01/23 18:46:26 by letnitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

int				g_info;

// il faut afficher un message de sortie: "exit" quand on clique sur ctrl+D
void handle_signal(int signo)
{
    // Vous pouvez personnaliser la gestion des signaux ici si nécessaire
    if (signo == SIGINT)
    {
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
        write(STDOUT_FILENO, "\n", 1);
    }
}

int ft_main(t_data *data, char *str, t_env *env)
{
    init_data(data, str);
    if (!is_closed_quotes(data))
        ft_error_2("unclosed quotes");
    ft_lexer(data);
    determine_token_types(data);
    if (!verif_syntax(data->token))
    {
        free_tokens(data->token);
        ft_error_2("syntax_erreur");
    }
    expand_tokens(data);
    parser(data);
    print_tokens(data->token);
    print_nodes(data);
	execute_command_node(data->node, env);
    return (0);
}

int	main(int argc, char *argv[], char **env)
{
    t_data data;
    t_env *my_env;
    char *command;

    if (argc > 1)
    {
        printf("minishell : parameters : bad usage\n");
        return (0);
    }
    argv[0] = '\0';
    signal(SIGINT, handle_signal);
    if (!env || !env[0])
        my_env = init_mini_env();
    else
        my_env = init_env(env);
    while (1)
    {
        command = readline("minishell> ");
        if (command == NULL)
        {
            printf("exit\n");
            break; // Sortir de la boucle si Ctrl+D est pressé
        }
        if (command && *command)
        {
            add_history(command);
            ft_main(&data, command, my_env);
            printf("\n");
        }
        free(command);
    }
    rl_clear_history();
	free_all(&data);
    return (0);
}

