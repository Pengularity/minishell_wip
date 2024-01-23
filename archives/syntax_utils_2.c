/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:04:16 by edesaint          #+#    #+#             */
/*   Updated: 2024/01/22 10:36:16 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// int int_deb_string_of_before(t_data *data, int i)
// {
//     i--;
//     while (i >= 0 && is_space(data->str[i]))
//         i--;
//     return (i);
// }

// bool deb_string_of_before(t_data *data, int i)
// {
//     i--;
//     while (i >= 0 && is_space(data->str[i]))
//         i--;
//     if (i < 0)
//         return (true);
//     return (false);
// }

// bool end_string_of_after(t_data *data, int i)
// {
//     i++;
//     while (data->str[i] && is_space(data->str[i]))
//         i++;
//     if (!data->str[i])
//         return (true);
//     return (false);
// }

// int int_deb_string_of_after(t_data *data, int i)
// {
//     i++;
//     while (data->str[i] && is_space(data->str[i]))
//         i++;
//     return (i);
// }

// void update_is_quote(t_data *data, char letter)
// {
//     if (is_quote(letter) && !data->in_quote)
//     {
//         data->type_quote = letter;
//         data->in_quote = 1;
//     }
//     else if (is_quote(letter) && data->in_quote)
//     {
//         if (letter == data->type_quote)
//         {
//             data->type_quote = '\0';
//             data->in_quote = 0;
//         }
//     }
// }