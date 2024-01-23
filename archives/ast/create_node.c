/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blax <blax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 14:59:37 by blax              #+#    #+#             */
/*   Updated: 2023/12/25 09:12:35 by blax             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast_node *create_command_node(char **args)
{
    t_ast_node *node;

    node = malloc(sizeof(t_ast_node));
    if (!node)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    node->type = AST_COMMAND;
    node->content.command.args = args;

    return (node);
}

t_ast_node *create_pipe_node(t_ast_node *left, t_ast_node *right)
{
    t_ast_node *node;
    
    node = malloc(sizeof(t_ast_node));
    if (!node)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    node->type = AST_PIPE;
    node->content.pipe.left = left;
    node->content.pipe.right = right;

    return (node);
}

t_ast_node *create_redirection_node(t_state type_redir, char *file, t_ast_node *child)
{
    t_ast_node *node;
    
    node = malloc(sizeof(t_ast_node));
    if (!node)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    node->type = AST_REDIRECT;
    node->content.redirect.type = type_redir;
    node->content.redirect.file = ft_strdup(file);
    node->content.redirect.child = child;
    
    return (node);
}