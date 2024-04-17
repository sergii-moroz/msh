NAME = minishell

LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g
CFLAGS =
MAKE	=	make
RM		=	rm -rf

LIB		=	-lreadline -lft -L$(LIBFT_DIR)
INC		=	-I includes

SRC_DIRS	=	src/lexer src src/darray src/cmd \
				src/parser src/executor src/envp \
				src/expander src/builtin src/redirection
vpath		%.c $(SRC_DIRS)

SRC		=	main.c \
			app.c env.c \
			lexer.c lexer_utils.c lexer_methods_1.c \
			lexer_methods_2.c lexer_methods_3.c lexer_token.c \
			error.c \
			darray.c darray_get.c darray_print.c \
			cmd.c cmd_get.c cmd_append.c cmd_utils.c\
			parser.c parser_utils.c \
			executor_new.c executor_utils.c executor_child.c \
			handle_cmd.c \
			builtin_utils.c ft_pwd.c ft_env.c ft_cd.c ft_exit.c ft_export.c ft_unset.c ft_echo.c \
			expander.c \
			redirection.c heredoc.c
#			envp.c envl.c envl_utils.c envl_utils2.c \
			executor.c \
			builtin1.c builtin_utils.c \
			ft_heredoc.c \
			token.c

OBJ_DIR	=	obj
OBJ	= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
#SRC	= $(addprefix $(SRC_DIR)/, $(SRC:.c=.o))

all: 		$(NAME)

$(NAME):	$(LIBFT) $(OBJ_DIR) $(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $@ $(CFLAGS) $(LIB)

$(LIBFT):
				cd $(LIBFT_DIR) && $(MAKE) bonus && $(MAKE) clean

$(OBJ_DIR):
				mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o:	%.c
				$(CC) -c $< -o $@ $(CFLAGS) $(INC)

clean:
			cd $(LIBFT_DIR) && $(MAKE) clean
			$(RM) $(OBJ_DIR)

fclean:		clean
			cd $(LIBFT_DIR) && $(MAKE) fclean
			$(RM) $(NAME)

re:			fclean all

run:		all
			./$(NAME)

test:
			echo $(OBJ)

val1:		all
			valgrind --leak-check=full --show-leak-kinds=all --show-reachable=yes ./minishell


.PHONY: all clean fclean re val test
