/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 10:02:39 by smoroz            #+#    #+#             */
/*   Updated: 2024/04/26 15:30:32 by smoroz           ###   ########.fr       */
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
//static void	parser_init(t_list *tokens, t_parser_data *data);
//static t_list	*parser_peek(t_parser_data *data)
int		parser_peek_type(t_parser_data *data);
t_darr	*parser(t_list *tokens, t_app *app);

//		parser_utils.c
void	parser_advance(t_parser_data *data);
void	parser_print_cmd(t_darr *darr);
int		parser_is_legrd(int type);
int		parser_is_argv(int type);

//		parser_utils_2.c
t_cmd	*parser_handle_pipe(t_darr **cmd_arr, t_cmd *cmd, t_parser_data *data);
void	parser_handle_argv(t_cmd **cmd, t_token *token);
void	parser_handle_redir(t_cmd **cmd, char *value, t_parser_data *data, t_app *app);
#endif
