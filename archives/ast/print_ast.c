/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blax <blax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 15:14:02 by blax              #+#    #+#             */
/*   Updated: 2024/01/14 20:27:53 by blax             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>

int compt_pipe(t_ast_node *node)
{
    if (node == NULL)
        return 0;

    int count = 0;
    if (node->type == AST_PIPE)
    {
        // Compter ce pipe
        count = 1;
        // Ajouter le nombre de pipes dans les sous-arbres gauche et droit
        count += compt_pipe(node->content.pipe.left);
        count += compt_pipe(node->content.pipe.right);
    }

    return count;
}

void print_ast_node(t_ast_node *node, int level)
{
    char **args;
    int i;

    if (!node) return;

    if (node->type == AST_COMMAND)
    {
        for (i = 0; i < level; i++)
            printf(" ");
        printf("COMMAND\n");
        level += 4;
        for (i = 0; i < level; i++)
            printf(" ");
        printf("|\n");
        for (i = 0; i < level; i++)
            printf(" ");
        printf("v\n");
        level -= 4;
        for (i = 0; i < level; i++)
            printf(" ");
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
            printf(" ");
        printf("PIPE\n");
        // ----------------------
        level -= 4;
        for (i = 0; i < level; i++)
            printf(" ");
        printf("/");
        for (i = 0; i < 8; i++)
            printf(" ");
        printf("\\\n");
        // ----------------------
        print_ast_node(node->content.pipe.right, level + 8);
        print_ast_node(node->content.pipe.left, level - 10);
    }
    else if (node->type == AST_REDIRECT)
    {
        for (i = 0; i < level; i++)
            printf(" ");
        printf("REDIRECTION: Type %d, Fichier '%s'\n", node->content.redirect.type, node->content.redirect.file);
        print_ast_node(node->content.redirect.child, level + 1);
    }
    else
    {
        for (i = 0; i < level; i++)
            printf(" ");
        printf("Type de noeud inconnu.\n");
    }
    printf("\n");
}

void print_ast(t_tree *tree)
{
    int i;

    i = compt_pipe(tree->ast) * (20 + 4) + 20 - 4;
    printf("i=%d\n", i);
    if (tree && tree->ast)
        print_ast_node(tree->ast, i);
    else
        printf("noeud vide.\n");
}