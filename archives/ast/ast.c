/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blax <blax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 23:20:44 by blax              #+#    #+#             */
/*   Updated: 2024/01/14 19:07:32 by blax             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void init_tree(t_tree **tree)
{
    *tree = malloc(sizeof(t_tree));
    if (!*tree)
        return ;
    (*tree)->current_command = NULL;
    (*tree)->ast = NULL;
    (*tree)->fd[IN] = STDIN_FILENO;
    (*tree)->fd[OUT] = STDOUT_FILENO;
}

t_ast_node *get_current_command(t_tree *tree, t_token **current_token)
{
    while (*current_token)
    {
        if ((*current_token)->type_token == T_COMMAND)
            update_ast_for_command(tree, *current_token);
        else if (is_redirection_token((*current_token)->type_token))
            update_ast_for_redirection(tree, *current_token);
        else if ((*current_token)->type_token == T_PIPE)
            return (tree->current_command);
        *current_token = (*current_token)->next;
    }

    return (tree->current_command);
}

t_ast_node *build_pipe_ast(t_tree *tree, t_token **current_token)
{
    t_ast_node *right_subtree;

    if (*current_token == NULL)
        return (tree->ast);
    while (*current_token != NULL)
    {
        *current_token = (*current_token)->next;
        right_subtree = get_current_command(tree, current_token);
        tree->ast = create_pipe_node(tree->ast, right_subtree);
    }
    return (tree->ast);
}

void build_ast(t_tree *tree, t_data *data)
{
    init_tree(&tree);
    t_token *current_token = data->token;
    tree->ast = get_current_command(tree, &current_token);
    tree->ast = build_pipe_ast(tree, &current_token);
    print_ast(tree);
}