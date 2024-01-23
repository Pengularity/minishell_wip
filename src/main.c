/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:53:55 by edesaint          #+#    #+#             */
/*   Updated: 2024/01/23 11:59:11 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int                g_info;

// il faut afficher un message de sortie: "exit" quand on clique sur ctrl+D
void handle_signal(int signo)
{
    if (signo == SIGINT)
    {
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
        write(STDOUT_FILENO, "\n", 1);
    }
}

int ft_main(t_data *data, char *str)
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
    return (0);
}

int main(int argc, char *argv[])
{
    t_data data;
    char *command;

    if (argc > 1)
    {
        printf("minishell : parameters : bad usage\n");
        return (0);
    }
    argv[0] = '\0';
    signal(SIGINT, handle_signal);
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
            ft_main(&data, command);
            printf("\n");
        }
        free(command);
    }
    rl_clear_history();
    free_all(&data);
    return (0);
}