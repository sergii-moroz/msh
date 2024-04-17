/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 10:02:39 by smoroz            #+#    #+#             */
/*   Updated: 2024/04/11 20:49:26 by smoroz           ###   ########.fr       */
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
//static int	parser_peek_type(t_parser_data *data);
t_darr		*parser(t_list *tokens, t_app *app);

//			parser_utils.c
void		parser_advance(t_parser_data *data);
void		parser_print_cmd(t_darr *darr);

#endif
