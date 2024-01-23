/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   off_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 18:26:34 by blax              #+#    #+#             */
/*   Updated: 2024/01/23 11:12:16 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int				g_info;

int main(int argc, char *argv[])
{
    t_data data;

    if (argc < 2)
        return (0);
    init_data(&data, argv[1]);
    if (!is_closed_quotes(&data))
        ft_error_2("unclosed quotes");
    ft_lexer(&data);
    determine_token_types(&data);
    if (!verif_syntax(data.token))
    {
        free_tokens(data.token);
        ft_error_2("syntax_erreur");
    }
    expand_tokens(&data);
    parser(&data);
    print_tokens(data.token);
    print_nodes(&data);
    free_all(&data);
    return (0);
}