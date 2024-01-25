# clear && make fclean && make tests && ./run_tests

SRC_DIR = src/
TEST_DIR = tests/
OBJ_DIR = obj/
OBJ_TEST_DIR = obj_tests/

SRC_FILES = main.c \
			transform_enum.c \
			syntax/syntax.c \
			syntax/syntax_utils_1.c \
			syntax/syntax_utils_2.c \
			syntax/syntax_utils_3.c \
			lexer/lexer.c \
			lexer/lexer_token.c \
			lexer/lexer_utils_1.c \
			lexer/lexer_utils_2.c \
			lexer/lexer_print.c \
			parser/parser.c \
			parser/parser_tab_exec.c \
			parser/parser_redir.c \
			parser/parser_redir_utils.c \
			parser/parser_utils_1.c \
			parser/parser_utils_2.c \
			parser/parser_node.c \
			parser/parser_getters.c \
			parser/parser_type_token.c \
			parser/parser_quote.c \
			parser/parser_print.c \
			expander/expander.c \
			expander/expander_utils_1.c \
			expander/expander_utils_2.c \
			trim.c \
			error.c \
			free/free.c \
			free/free_2.c \
			builtins/ft_cd.c \
			builtins/ft_echo.c \
			builtins/ft_env.c \
			builtins/ft_exit.c \
			builtins/ft_pwd.c \
			builtins/ft_unset.c \
			builtins/ft_export.c \
			exec/exec.c \
			exec/exec_builtin.c \
			exec/exec_cmd.c \
			exec/get_path.c \
			exec/exec_pipeline.c \
			init/init_data.c \
			init/init_env.c \
			env/env_utils.c \
			signals/signals.c \
			# exec/file_redir.c \

# TEST_FILES = common/ts_common.c \
# 			lexer/ts_1.c \
# 			lexer/ts_2.c \
# 			lexer/ts_3.c \
# 			lexer/ts_4.c \
# 			lexer/ts_5.c

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
TEST = $(addprefix $(TEST_DIR), $(TEST_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))
OBJ_TEST = $(addprefix $(OBJ_TEST_DIR), $(TEST_FILES:.c=.o))

# DEPS = $(OBJ:.o=.d)

# Modification des règles pour utiliser les nouveaux chemins d'objets
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_TEST_DIR)%.o: $(TEST_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


# /* ~~~~~~~ INCLUDING LIBFT ~~~~~~~ */
LIBFT_DIR = libft
LIBFT_MAKE = Makefile
LIBFT_PATH = ${LIBFT_DIR}/libft.a

# /* ~~~~~~~ COMPILING INFO ~~~~~~~ */
CC = gcc # CC = clang
CFLAGS = -Wall -Wextra -Werror -g # -MMD -MP
LIBFT_FLAGS = -L $(LIBFT_DIR) -lft
CRITERION_FLAGS = -lcriterion
INCLUDES = -I ./include

# /* ~~~~~~~ OTHER ~~~~~~~ */
NAME = minishell
TEST_NAME = run_tests
RM = rm -f

# /* ~~~~~~~ Colors ~~~~~~~ */
BLACK:="\033[1;30m"
RED:="\033[1;31m"
GREEN:="\033[1;32m"
PURPLE:="\033[1;35m"
CYAN:="\033[1;36m"
WHITE:="\033[1;37m"
EOC:="\033[0;0m"

all: $(NAME)

$(NAME): $(OBJ)
	@cd $(LIBFT_DIR) && $(MAKE) bonus
	@echo $(CYAN) " - Compiling $@" $(RED)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT_FLAGS) -lreadline
	@echo $(GREEN) "[OK COMPILED]" $(EOC)

# tests: $(OBJ) $(OBJ_TEST)
# 	@echo $(CYAN) " - Compiling $@" $(RED)
# 	@cd $(LIBFT_DIR) && $(MAKE)
# 	$(CC) $(CFLAGS) $(INCLUDES) -o $(TEST_NAME) $(OBJ) $(OBJ_TEST) $(LIBFT_PATH) $(CRITERION_FLAGS)
# 	@echo $(GREEN) "[OK COMPILED]" $(EOC)

clean:
	@echo $(PURPLE) "[🧹Cleaning...🧹]" $(EOC)
	@${RM} -r $(OBJ_DIR)
	@${RM} -r $(OBJ_TEST_DIR)
	# @${RM} $(DEPS)
	@make -C ${LIBFT_DIR} -f ${LIBFT_MAKE} fclean

fclean: clean
	@echo $(PURPLE) "[🧹FCleaning...🧹]" $(EOC)
	@${RM} $(NAME)
	@${RM} $(TEST_NAME)

re: fclean all

.PHONY:		all clean fclean re

# -include $(DEPS)
