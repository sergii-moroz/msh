/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 12:07:45 by smoroz            #+#    #+#             */
/*   Updated: 2024/03/31 12:07:45 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include "colors.h"
# include "common.h"
# include "../libft/libft.h"

# define LESS	1
# define GREAT	2
# define PIPE	3
# define PARE_L	4
# define PARE_R	5

# define WORD	6
# define QUOTE	7
# define DQUOTE	8
# define DLESS	9
# define DGREAT	10
# define IF_AND	11
# define IF_OR	12
# define NUM	13
# define SPACES	14

typedef struct s_token
{
	char	*value;
	int		type;
}			t_token;

typedef struct s_lexer_data
{
	char	*s;
	int		i;
	char	current_char;
	int		had_error;
}			t_lexer_data;

//			lexer.c
// static void		lexer_init(char *s, t_lexer_data *data);
// static void		skip_spaces(t_lexer_data *data);
// static t_token	*get_next_token(t_lexer_data *data);
void		advance(t_lexer_data *data);
t_list		*lexer(char *line);

//			lexer_methods_1.c
// static char	*cut_quote(t_lexer_data *data);
// static char	*cut_word(t_lexer_data *data);
t_token		*lexer_get_quote(t_lexer_data *data);
t_token		*lexer_get_word(t_lexer_data *data);
t_token		*lexer_get_parentheses(t_lexer_data *data);

//			lexer_methods_2.c
// static char	*cut_number(t_lexer_data *data);
// static char	peek(t_lexer_data *data);
t_token		*lexer_get_number(t_lexer_data *data);
t_token		*lexer_get_legraor(t_lexer_data *data);
int			is_null(char *str, t_lexer_data *data);

//			lexer_methods_3.c
// static char	*cut_spaces(t_lexer_data *data);
t_token		*lexer_get_spaces(t_lexer_data *data);

//			lexer_utils.c
int			is_less_great_or_and(int c);
int			is_quote(int c);

//			lexer_token.c
t_token		*token_new(char *s, int type);
void		token_destroy(void *token);
void		token_print(void *token);
void		token_set_type(t_token *token);

//			error.c
void		error(char *where, char *message);

#endif
