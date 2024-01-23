/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blax <blax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 15:14:02 by blax              #+#    #+#             */
/*   Updated: 2024/01/14 18:24:40 by blax             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>

void print_ast_node(t_ast_node *node, int level)
{
    char **args;
    int i;

    if (!node) return;

    // Créer une indentation basée sur le niveau de profondeur du nœud
    for (i = 0; i < level; i++)
        printf("  ");

    // Afficher le type de nœud avec l'indentation
    printf("Type de noeud: %d\n", node->type);

    // Selon le type de nœud, afficher les attributs correspondants avec l'indentation
    if (node->type == AST_COMMAND)
    {
        for (i = 0; i < level; i++)
            printf("  ");
        printf("Commande: ");
        if (node->content.command.args)
        {
            args = node->content.command.args;
            while (*args != NULL)
            {
                printf("'%s' ", *args);
                args++;
            }
        }
        printf("\n");
    }
    else if (node->type == AST_PIPE)
    {
        for (i = 0; i < level; i++)
            printf("  ");
        printf("Pipe:\n");
        print_ast_node(node->content.pipe.left, level + 1);
        print_ast_node(node->content.pipe.right, level + 1);
    }
    else if (node->type == AST_REDIRECT)
    {
        for (i = 0; i < level; i++)
            printf("  ");
        printf("Redirection: Type %d, Fichier '%s'\n", node->content.redirect.type, node->content.redirect.file);
        print_ast_node(node->content.redirect.child, level + 1);
    }
    else
    {
        for (i = 0; i < level; i++)
            printf("  ");
        printf("Type de noeud inconnu.\n");
    }
    printf("\n");
}

void print_ast(t_tree *tree)
{
    if (tree && tree->ast)
        print_ast_node(tree->ast, 0);
    else
        printf("noeud vide.\n");
}