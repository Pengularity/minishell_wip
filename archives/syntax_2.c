/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:48:38 by edesaint          #+#    #+#             */
/*   Updated: 2024/01/22 10:36:01 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// bool check_syntax_before(t_data *data, int i)
// {
//     char letter;
//     int deb_string;
    
//     letter = data->str[i];
//     if (deb_string_of_before(data, i) && letter == '|')
//         return (true);
//     if (!deb_string_of_before(data, i))
//     {
//         deb_string = int_deb_string_of_before(data, i);
//         if (deb_string > 0)
//         {
//             if (letter == '>' || letter == '<')
//             {
//                 if (data->str[deb_string] == '>' || data->str[deb_string] == '<')
//                     return (true);
//             }
//         }
//     }
//     return (false);
// }

// bool check_syntax_after_pipe(t_data *data, int i)
// {
//     if (end_string_of_after(data, i))
//         return (true);
//     if (data->str[i] == '|')
//         return (true);
//     return (false);
// }

// bool check_syntax_after(t_data *data, int i)
// {
//     char letter;
//     int deb_string;
    
//     letter = data->str[i];
//     deb_string = int_deb_string_of_after(data, i);
//     if (letter == '>' || letter == '<')
//     {
//         if (data->str[deb_string] == '>' || data->str[deb_string] == '<')
//             return (true);
//     }
//     return (false);
// }

// void verif_syntax(t_data *data)
// {
//     int i;

//     i = 0;
//     while (data->str[i])
//     {
//         update_is_quote(data, data->str[i]);
//         if (is_syntax_char(data->str[i]) && !data->in_quote)
//         {
//             if (check_syntax_before(data, i))
//                 ft_error_2("Syntax error before");
//             if (is_double_symbol(data, i, '<') || 
//                 is_double_symbol(data, i, '>'))
//             {
//                 i++;
//             }
//             if (check_syntax_after(data, i))
//                 ft_error_2("Syntax error after");
//         }
//         i++;
//     }
// }

// void ft_unclosed_quotes(t_data *data)
// {
//     int i;

//     i = 0;
//     while (data->str[i])
//     {
//         update_is_quote(data, data->str[i]);
//         i++;
//     }
//     if (!data->str[i] && data->in_quote)
//         ft_error_2("Error unclosed quotes !");
// }