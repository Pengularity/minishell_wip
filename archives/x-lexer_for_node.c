/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:08:04 by blax              #+#    #+#             */
/*   Updated: 2024/01/17 13:16:45 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void process_space(t_data *data, int *i)
{
    while (data->str[*i] && !is_syntax(data->str[*i]))
        (*i)++;
    if (is_syntax(data->str[*i]))
        (*i)--;
}

/* Crée un nouveau token avec les données fournies et le retourne. */
t_token *create_token(t_data *data, t_node *node, int end)
{
    t_token *token;
    int len;
    
    len = end - node->start_token;
    token = malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->id = node->nb_tokens;
    token->type_token = T_NULL;
    token->str = ft_substr(data->str, (unsigned int) node->start_token, (size_t) len);
    token->type_str = ft_type_char(data->str[--end]);
    token->type_stick = ft_type_char(data->str[++end]);
    token->prev = NULL;
    token->next = NULL;
    
    return (token);
}

/* Ajoute un nouveau token à la liste chaînée de tokens dans 'data'. */
void add_token(t_data *data, t_node *node, int end)
{
    t_token *new_token;
    t_token *temp;

    new_token = create_token(data, node, end);
    if (new_token)
    {
        if (node->tokens == NULL)
        {
            new_token->prev = NULL;
            node->tokens = new_token;
        }
        else
        {
            temp = node->tokens;
            while (temp->next != NULL)
                temp = temp->next;
            new_token->prev = temp;
            temp->next = new_token;
        }
    }
}

/* Traite une séquence de guillemets dans la chaîne de caractères de 'data'. */
bool process_quote(t_data *data, int *i)
{
    char type_quote;

    if (!data->str[*i])
        return (false);
    if (!is_quote(data->str[*i]))
        return (false);
    type_quote = data->str[*i];
    (*i)++;
    while (data->str[*i])
    {
        if (data->str[*i] && is_quote(data->str[*i]))
        {
            if (data->str[*i] == type_quote)
            {
                (*i)++;
                return (true);
            }
        }
        (*i)++;
    }
    return (true);
}

bool in_node(t_data *data, int i)
{
    return (i > data->start_node && i < data->end_node);
}

/* Analyse la chaîne de caractères 'str' et remplit 'data' avec les tokens. */
void lexer_node(t_data *data, t_node *node)
{
    int i;
    int result;
    t_node *node;

    i = data->start_node;
    while (data->str[i] && in_node(data, i))
    {
        skip_spaces(data, &i);
        node->start_token = i;
        result = process_quote(data, &i);
        if (result == 0)
            process_space(data, &i);
        add_token(data, node, i);
        node->nb_tokens++;
        i++;
    }
}