/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blax <blax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:02:23 by blax              #+#    #+#             */
/*   Updated: 2024/01/14 17:20:24 by blax             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void update_ast_for_command(t_tree *tree, t_token *current_token)
// {
//     char **args;
//     t_ast_node *current_node;

//     args = collect_args(&current_token);
//     current_node = create_command_node(args);
//     tree->current_command = current_node;
// }

void update_ast_for_command(t_tree *tree, t_token *current_token)
{
    char **args;
    t_ast_node *current_node;

    if (!tree)
        ft_error("Erreur : 'tree' est NULL.\n");
    if (!current_token)
        ft_error("Erreur : 'current_token' est NULL.\n");
    args = collect_args(&current_token);
    if (!args)
        ft_error("Erreur : 'collect_args' a renvoyé NULL.\n");
    current_node = create_command_node(args);
    if (!current_node)
        ft_error("Erreur : 'create_command_node' a renvoyé NULL.\n");
    tree->current_command = current_node;
    // print_ast(tree);
}

void update_ast_for_redirection(t_tree *tree, t_token *current_token)
{
    t_ast_node *current_node;

    current_node = create_redirection_node(
        current_token->type_token,
        current_token->str,
        tree->current_command
    );
    tree->current_command = current_node;
    // print_ast(tree);
}

// void update_ast_for_pipe(t_tree *tree)
// {
//     t_ast_node *current_node;

//     // s'il n'y a rien sauf un pipe, alors erreur
//     // puisque le prompt doit commencer par une commande
//     if (tree->ast == NULL)
//         ft_error("pipe is not a command");
//     else
//     {
//         current_node = create_pipe_node(tree->ast, NULL);
//         tree->ast = current_node;
//     }
//     tree->current_command = tree->ast->content.pipe.right;
//     // print_ast(tree);
// }
