/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 20:01:20 by edesaint          #+#    #+#             */
/*   Updated: 2024/01/17 14:58:18 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool is_quote(char c)
{
    return (c == '\'' || c == '"');
}

bool is_space(char c)
{
    return (c == ' ' || c == '\t'); // implementer les autres
}

bool is_syntax_char(char c)
{
    return (c == '|' || c == '>' || c == '<');
}

bool is_syntax(char c)
{
    return (is_space(c) || is_quote(c) || is_syntax_char(c));
}

bool is_double_symbol(t_data *data, int i, char c)
{
    return (data->str[i] == c && data->str[++i] == c);
}