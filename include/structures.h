/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:19:02 by blax              #+#    #+#             */
/*   Updated: 2024/01/23 14:11:08 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <stdbool.h>
# include "enum.h"

// typedef struct s_redirect
// {
//     t_state             type;
//     char                *file;
//     struct s_redirect *next;
// } t_redirect;

// Structure représentant un élément d'environnement(KEY=VALUE).
typedef struct s_env_element
{
	char					*key;
	char					*value;
	struct s_env_element	*next;
	struct s_env_element	*prev;
}		t_env_element;

// Structure représentant l'environnement complet.
typedef struct s_env
{
	unsigned int			len;
	unsigned int			last_exit_status;
	struct s_env_element	*first;
	struct s_env_element	*last;
}		t_env;

typedef struct s_token
{
	int				id;
	char			*str;
    bool            is_space;
	t_stick_token	type_str;
	t_stick_token	type_rstick;
	t_stick_token	type_lstick;
	t_state			type_token;
	//int nb_space;
	// int nb_two_double_quotes;
	// int nb_two_single_quotes;
	struct s_token	*next;
    struct s_token	*prev;
}				t_token;

typedef struct s_node
{
    int                 id;
    bool				type;
    char                **tab_exec;
    char			    *redir_in;
	char				*redir_out;
	char				*redir_append;
	char				*redir_heredoc;
	struct s_node       *next;
} t_node;

typedef struct s_parsed_cmd
{
	unsigned int	nb_nodes;
	t_node			*first_node;
	t_node			*last_node;
}			t_parsed_cmd;

typedef struct s_data
{
    int             start;
    int             end;
    int             nb_tokens;
    int             nb_nodes;
    bool            is_space;
    char            type_quote;
    char            in_quote;
	int				lst_exit; //dernier statue de sortie
    char            *str;
    struct s_token	*token;
	struct s_node	*node;
}				t_data;

#endif
