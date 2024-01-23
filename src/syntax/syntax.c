/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:48:38 by edesaint          #+#    #+#             */
/*   Updated: 2024/01/22 11:01:54 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool verif_syntax(t_token *token)
{
    if (is_begin_by_pipe(token))
        return (false);
    if (is_end_by_pipe(token))
        return (false);
    if (!is_valid_redir(token))
        return (false);
    return (true);
}