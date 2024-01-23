/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:10:16 by blax              #+#    #+#             */
/*   Updated: 2024/01/17 19:47:13 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void remove_quotes(char *input, char type_quote)
{
    size_t len;

    len = ft_strlen(input);
    if (len >= 2 && input[0] == type_quote && input[len - 1] == type_quote)
    {
        ft_memmove(input, input + 1, len - 2);
        input[len - 2] = '\0';
    }
}

void parse_quote_tokens(t_data *data)
{
	t_token *current_token;

	current_token = data->token;
    while (current_token != NULL)
	{
        if (current_token->type_str == S_QUOTE)
			remove_quotes(current_token->str, '\'');
		else if (current_token->type_str == D_QUOTE)
			remove_quotes(current_token->str, '"');
        current_token = current_token->next;
    }
}

// X
// il ne peut plus y avoir de null token car gerer en amont
// C'est mieux de parcourir la liste des tokens
// mais voici la fonction pour la modifier
// et enlever les double quotes ou single quotes vides
// void remove_null_tokens(t_token **token_list)
// {
//     t_token *current;
//     t_token *temp;

//     current = *token_list;
//     while (current != NULL)
//     {
//         if (is_empty_token(current))
//         {
//             temp = current;
//             if (current->prev)
//                 current->prev->next = current->next;
//             else
//                 *token_list = current->next; // Mise à jour de la tête de la liste si le premier token est supprimé

//             if (current->next)
//                 current->next->prev = current->prev;

//             current = current->next;
//             free(temp->str); // Libérer la chaîne de caractères du token
//             free(temp);      // Libérer le token lui-même
//         }
//         else
//         {
//             current = current->next;
//         }
//     }
// }