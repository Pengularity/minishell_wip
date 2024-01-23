/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:22:37 by blax              #+#    #+#             */
/*   Updated: 2024/01/22 21:27:59 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H

typedef enum e_status {
	SUCCESS = 1,
	FAILURE = 0
}	t_status;

typedef enum e_redir {
	OUT = 1,
	IN = 0
}	t_redir;

// faire un boolen dans node
typedef enum e_type_node {
	N_CMD,
	N_ERROR
}		t_type_node;

typedef enum e_state {
	T_NULL,
	T_COMMAND,
	T_OPTION,
	T_ARGUMENT,
	T_PIPE,
	T_FILE,
	T_REDIR_IN,      // <
    T_REDIR_OUT,     // >
    T_REDIR_APPEND,  // >>
    T_REDIR_HEREDOC  // <<
}	t_state;

typedef enum e_stick_token {
	S_NULL,
	S_QUOTE,
	D_QUOTE,
	S_CHAR,
	S_SYNTAX,
	S_SPACE,
}	t_stick_token;

#endif