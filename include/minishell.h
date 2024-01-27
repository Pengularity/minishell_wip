/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 08:31:10 by blax              #+#    #+#             */
/*   Updated: 2024/01/27 17:02:38 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "enum.h"
# include "structures.h"
# include "libft.h"

# define _POSIX_C_SOURCE 200809L
# include <signal.h>
# include <unistd.h> // access
# include <stdlib.h> // malloc
# include <readline/readline.h> // readline
# include <readline/history.h> // addhistory
# include <sys/wait.h> //wait
# include <stdio.h>
# include <stdbool.h>
# include <errno.h>
// # include <bsd/string.h>
// # include <stddef.h> //ft_strcmp

extern int	g_info;

// transform_enum.c
t_stick_token	ft_type_char(char c);
char			*transform_enum_type_token(t_state num_c);
char			*transform_enum_quote(t_stick_token num_c);
char			*transform_enum_type_node(t_type_node num_c);

//builtins.c
int				ft_cd(t_node *node, t_env *env);
int				ft_echo(t_node *node, t_env *env);
int				ft_env(t_node *node, t_env *env);
int				ft_pwd(t_node *node, t_env *env);
int				ft_unset(t_node *node, t_env *env);
int				ft_exit(t_node *node, t_env *env);
int				ft_export(t_node *node, t_env *env);

//ft_unset.c util
int				is_valid_env_name(const char *str);

//env_utils.c
void			add_env_var(t_env *env, const char *name, const char *content);
void			update_env_var(t_env *env, const char *name,
					const char *content);
char			*get_env_name(t_env *env, const char *name);
char			*join_var_in_str(t_env_link *env_link);
char			**convert_env_to_tab(t_env *env);
void			update_shlvl(t_env *env);

//ft_unset.c
int				is_valid_env_name(const char *str);
void			unset_error(char *arg);

// syntax_utils_1.c
bool			is_quote(char c);
bool			is_space(char c);
bool			is_syntax_char(char c);
bool			is_syntax(char c);
bool			is_double_symbol(t_data *data, int i, char c);

// syntax_utils_2.c
// int int_deb_string_of_before(t_data *data, int i);
// bool deb_string_of_before(t_data *data, int i);
// bool end_string_of_after(t_data *data, int i);
// int int_deb_string_of_after(t_data *data, int i);
void			update_is_quote(t_data *data, char letter);
bool			is_closed_quotes(t_data *data);

// syntax_utils_3.c
bool			is_syntax_redir(char *str);
bool			is_begin_by_pipe(t_token *token);
bool			is_end_by_pipe(t_token *token);
bool			check_redir(t_token *token);
bool			is_valid_redir(t_token *token);

// syntax.c
bool			verif_syntax(t_token *token);
// bool check_before(t_data *data, int i);
// bool check_after(t_data *data, int i);

// trim.c
int				nb_trim_left(char *str);
int				nb_trim_right(char *str);
char			*trim_str(char *str);

// ----------------------------------------------------------------------

// free.c
void			free_tab_exec(char **tab_exec);
void			free_nodes(t_node *node);
void			free_tokens(t_token *token);
void			free_data(t_data *data);

// free_2.c
void			free_all(t_data *data);

// error.c
bool			ft_error(char *str);
void			ft_error_2(char *str);

// ------------------ Init --------------------

// init_env.c
t_env_link		*env_new_link(char *str);
void			env_connect_links(t_env_link *prev, t_env_link *current);
t_env			*init_mini_env(void);
t_env			*init_env(char **system_env);

//init_data.c
void			init_data(t_data *data, char *str);

// ------------------ Lexer --------------------
// lexer.c
bool			ft_lexer(t_data *data);
bool			process_string(t_data *data, int *i);
bool			process_quote(t_data *data, int *i);
bool			process_syntax(t_data *data, int *i);

// lexer_utils_1.c
int				set_len(t_data *data, int end);
bool			skip_spaces(t_data *data, int *i);
bool			is_empty_quotes(t_data *data, int *i);

// lexer_utils_2.c
void			ft_token_add_back(t_token **token, t_token *newlist);
t_token			*ft_token_last(t_token *token);
void			ft_token_iter(t_token *token, void (*f)(void *));

// lexer_token.c
t_stick_token	set_type_lstick(t_data *data);
t_token			*create_token(t_data *data, int end, int len);
bool			add_token(t_data *data, int end, int len);

void			process_for_token(t_data *data, int *i);
// void lexer_node(t_data *data, t_node *node);

// lexer_print.c
void			print_tokens(t_token *tokens);

// ------------------ Parser --------------------

// parser.c
void			parser(t_data *data);

// parser_utils_1.c
bool			is_command(bool *is_cmd, t_state cur_state);
bool			is_pipe(char *str, bool *is_cmd);
bool			is_redirection(char *str);
t_state			what_redirection(char *str);
bool			is_file_redirection(t_state cur_state);
bool			is_type_redir(t_state type_token);

// parser_utils_2.c
bool			in_node(t_data *data, t_token *token);
int				compt_args(t_data *data);
int				compt_nodes(t_data *data);

// parser_print.c
void			print_tab_exec(t_node *node);
void			print_redir(t_node *node);
void			print_nodes(t_data *data);

// parser_node.c
t_node			*create_node(t_data *data);
void			add_node(t_data *data);
void			init_nodes(t_data *data);
bool			fill_nodes(t_data *data);
bool			delimit_node(t_data *data, t_token *token);

// parser_redir.c
bool			is_redir_append(t_token *token, char *name);
bool			is_redir_out(t_token *token, char *name);
bool			is_redir_in(t_token *token, char *name);
// bool is_redir_heredoc(t_token *token, char *name);
bool			update_redir(t_node *node, t_token *token);
bool			init_redir(t_data *data, t_node *node, t_token *token);

// parser_redir_utils.c
bool			is_redir(t_state type);
bool			is_file_redir(t_token *token);
char			*get_name_redir(t_token *token);

// parser_getters.c
t_token			*get_first_token(t_data *data, t_node *node, t_token *token);
t_token			*get_end_token(t_data *data, t_token *token);
char			*get_argument(t_data *data, t_token *token);
char			*get_command(t_token *token);

// parser_tab_exec.c
char			**create_tab_exec(t_data *data, t_token *token, int nb_args);
char			**init_tab_exec(t_data *data, t_token *token);

// parser_quote.c
void			parse_quote_tokens(t_data *data);
void			remove_quotes(char *input, char type_quote);

// parser_type_token.c
void			update_token_type(t_token *token, bool *is_cmd,
					t_state cur_state);
void			determine_token_types(t_data *data);
void			determine_next_token_type(t_state type_token,
					t_state *cur_state);

// ------------------ Expander --------------------

// expander.c
bool			is_expandable(t_token *token);
void			expand_tokens(t_data *data);
void			replace_token_str(t_token *token, char *new_value);
// void print_expanded_tokens(t_token *tokens);

// expander_utils_1.c
char			*expand_variables(const char *input);
char			*process_dollar_sign(const char **ptr, char *result);
char			*process_text_until_next_dollar(const char **ptr, char *result);

// expander_utils_2.c
char			*append_variable_value(char *result, const char *varName);
char			*extract_var_name(const char **ptr);
char			*copy_until_char(char *dest, const char *src, char delimiter);

// ------------------ EXEC --------------------
//exec.c
void			execute_command_node(t_node *node, t_env *env);
int				builtin_command(t_node *node, t_env *env, int pid);
bool			is_builtin(t_node *node);
char			*get_cmd_path(char *cmd, char **envp);
int				exec_builtin(t_node *node, t_env *env);
int				execute_command(t_node *node, char **envp);
// void	exec_pipeline(t_node *node, char **envp, t_env *env);
void			exec_pipeline(t_node *node, t_env *env);
int				exec_redir(t_node *node);

// signals.c

void			handle_sigint(int signum);
bool			handle_ctrl_d(char *input);

#endif
