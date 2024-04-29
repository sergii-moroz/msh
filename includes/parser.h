/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 10:02:39 by smoroz            #+#    #+#             */
/*   Updated: 2024/04/29 07:52:31 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "darray.h"
# include "colors.h"
# include "cmd.h"
# include "lexer.h"
# include "app.h"

typedef struct s_parser_data
{
	t_list	*tokens;
	t_list	*current_token;
	int		had_error;
}			t_parser_data;

//			parser.c
int		parser_peek_type(t_parser_data *data);
void	parser(t_list *tokens, t_app *app);

//		parser_utils_1.c
void	parser_advance(t_parser_data *data);
void	parser_print_cmd(t_darr *darr);
int		parser_is_legrd(int type);
int		parser_is_argv(int type);

//		parser_utils_2.c
t_cmd	*parser_handle_pipe(t_app *app, t_cmd *cmd, t_parser_data *data);
void	parser_handle_argv(t_cmd **cmd, t_token *token);
void	handle_redir(t_cmd **cmd, char *value, t_parser_data *data, t_app *app);
#endif
