/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letnitan <letnitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:25:07 by letnitan          #+#    #+#             */
/*   Updated: 2024/01/23 18:19:39 by letnitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void init_data(t_data *data, char *str)
{
    data->start = 0;
    data->end = 0;
    data->node = NULL;
    data->nb_tokens = 0;
    data->nb_nodes = 0;
    data->token = NULL;
    data->is_space = false;
    data->type_quote = '\0';
    data->in_quote = 0;
    data->str = trim_str(str);
}
