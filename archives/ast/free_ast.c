/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blax <blax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 10:05:16 by blax              #+#    #+#             */
/*   Updated: 2023/12/19 20:38:15 by blax             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void free_tree(t_tree *tree)
{
    if (tree->ast != NULL)
        free_ast(tree->ast);
    if (tree->current_command != NULL)
        free(tree->current_command);
}

void free_ast(t_ast_node *ast)
{
    int i;

    if (ast == NULL)
        return ;
    i = 0;
    if (ast->type == AST_COMMAND)
    {
        while (ast->content.command.args[i] != NULL)
        {
            free(ast->content.command.args[i]);
            i++;
        }
        free(ast->content.command.args);
    }
    else if (ast->type == AST_PIPE)
    {
        free_ast(ast->content.pipe.left);
        free_ast(ast->content.pipe.right);
    }
    else if (ast->type == AST_REDIRECT)
    {
        free(ast->content.redirect.file);
        free_ast(ast->content.redirect.child);
    }
    free(ast);
}