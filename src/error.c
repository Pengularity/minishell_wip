/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 23:46:52 by blax              #+#    #+#             */
/*   Updated: 2024/01/22 12:11:59 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool ft_error(char *str)
{
    perror(str);
    return (false);
}

void ft_error_2(char *str)
{
    perror(str);
    exit (FAILURE);
}