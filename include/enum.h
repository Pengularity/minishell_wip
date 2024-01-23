/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:22:37 by blax              #+#    #+#             */
/*   Updated: 2024/01/23 11:44:55 by edesaint         ###   ########.fr       */
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
	IN
}	t_redir;

typedef enum e_state {
	T_NULL,
	T_COMMAND,
	T_OPTION,
	T_ARGUMENT,
	T_PIPE,
	T_FILE,
	T_REDIR_IN,
    T_REDIR_OUT,
    T_REDIR_APPEND,
    T_REDIR_HEREDOC
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