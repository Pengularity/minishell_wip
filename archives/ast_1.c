/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blax <blax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 23:20:44 by blax              #+#    #+#             */
/*   Updated: 2024/01/14 17:10:16 by blax             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//non-fonctionnel

#include "../../include/minishell.h"

void init_tree(t_tree **tree)
{
    *tree = malloc(sizeof(t_tree));
    if (!*tree)
        return ;
    (*tree)->current_command = NULL;
    (*tree)->ast = NULL;
    (*tree)->in_pipe = 0;
    (*tree)->is_pipe = 0;
    (*tree)->fd[IN] = STDIN_FILENO;
    (*tree)->fd[OUT] = STDOUT_FILENO;
}

// void build_ast(t_tree *tree, t_data *data)
// {
//     t_token *current_token;
    
//     init_tree(&tree);
//     current_token = data->token;
//     while (current_token)
//     {
//         if (current_token->type_token == T_COMMAND)
//             update_ast_for_command(tree, current_token);
//         else if (is_redirection_token(current_token->type_token))
//             update_ast_for_redirection(tree, current_token);
//         else if (current_token->type_token == T_PIPE)
//             update_ast_for_pipe(tree);
//         current_token = current_token->next;
//     }
//     if (tree->ast == NULL)
//         tree->ast = tree->current_command;
// }

// fonctionnel mais pas le bon ordre des pipes
// void update_ast_for_pipe(t_tree *tree, t_token **current_token)
// {
//     t_ast_node *left_subtree = tree->current_command; // L'AST actuel est le sous-arbre gauche.
//     t_ast_node *right_subtree;

//     // Avancer le token actuel pour passer le pipe.
//     *current_token = (*current_token)->next;

//     // Construire le sous-arbre droit récursivement.
//     right_subtree = build_ast_recursive(tree, current_token);

//     // Créer le nœud de pipe et mettre à jour l'AST de l'arbre.
//     tree->ast = create_pipe_node(left_subtree, right_subtree);
//     // Mettre à jour current_command pour refléter la commande la plus à droite.
//     tree->current_command = right_subtree;
// }

// non-fonctionnel
// void update_ast_for_pipe(t_tree *tree, t_token **current_token)
// {
//     t_ast_node *left_subtree = tree->current_command; // L'AST actuel est le sous-arbre gauche.
//     t_ast_node *right_subtree;

//     // Avancer le token actuel pour passer le pipe.
//     *current_token = (*current_token)->next;

//     // Construire le sous-arbre droit récursivement.
//     right_subtree = build_ast_recursive(tree, current_token);

//     // Si l'AST de l'arbre est déjà un nœud de pipe, attacher le nouveau nœud de pipe à droite.
//     if (tree->ast && tree->ast->type == AST_PIPE)
//     {
//         t_ast_node *last_pipe = tree->ast;
//         while (last_pipe->content.pipe.right && last_pipe->type == AST_PIPE)
//         {
//             last_pipe = last_pipe->content.pipe.right;
//         }
//         last_pipe->content.pipe.right = create_pipe_node(left_subtree, right_subtree);
//     }
//     else
//     {
//         // Sinon, créer le nœud de pipe et mettre à jour l'AST de l'arbre.
//         tree->ast = create_pipe_node(left_subtree, right_subtree);
//     }

//     // Mettre à jour current_command pour refléter la commande la plus à droite.
//     tree->current_command = right_subtree;
// }

// Cette fonction est appelée récursivement pour construire l'AST.
t_ast_node *build_ast_recursive(t_tree *tree, t_token **current_token)
{
    t_ast_node *right_subtree;

    if (!*current_token)
        return (NULL);

    while (*current_token)
    {
        if ((*current_token)->type_token == T_COMMAND)
            update_ast_for_command(tree, *current_token);
        else if (is_redirection_token((*current_token)->type_token))
            update_ast_for_redirection(tree, *current_token);
        else if ((*current_token)->type_token == T_PIPE)
        {
            if (tree->ast == NULL && tree->side_pipe == 0)
                tree->ast = tree->current_command;
            else if (tree->ast != NULL && tree->side_pipe == 1)
                return tree->current_command;
            tree->side_pipe = 1;
            while (tree->side_pipe == 1)
                right_subtree = build_ast_recursive(tree, current_token++);
                tree->ast = create_pipe_node(tree->ast, right_subtree);
        }
        if (*current_token != NULL)
            *current_token = (*current_token)->next;
    }
// a gerer avec un tree->is_pipe
    if (tree->side_pipe == 1)
    {
        tree->side_pipe = 0;
        return tree->current_command;
    }
    if (tree->side_pipe == 0)
        return tree->ast;
    return tree->current_command;
}

// Dans ast.c

void build_ast(t_tree *tree, t_data *data)
{
    init_tree(&tree);
    t_token *current_token = data->token;
    tree->ast = build_ast_recursive(tree, &current_token);
    print_ast_node(tree->ast, 0);
}