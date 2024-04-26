/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:38:04 by olanokhi          #+#    #+#             */
/*   Updated: 2024/04/26 15:31:20 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

t_cmd	*parser_handle_pipe(t_darr **cmd_arr, t_cmd *cmd, t_parser_data *data)
{
	darray_append(*cmd_arr, cmd);
	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		exit(1); //TODO proper exit
	cmd_init(cmd);
	if (parser_peek_type(data) == SPACES)
		parser_advance(data);
	return (cmd);
}

void	parser_handle_redir(t_cmd **cmd, char *value, t_parser_data *data, t_app *app)
{
	t_token	*token;

	cmd_append_redir(*cmd, value);
	if (parser_peek_type(data) == SPACES)
		parser_advance(data);
	if (parser_peek_type(data) == WORD \
		|| parser_peek_type(data) == DQUOTE \
		|| parser_peek_type(data) == QUOTE
		|| parser_peek_type(data) == NUM)
	{
		parser_advance(data);
		token = data->current_token->content;
		cmd_append_redir(*cmd, token->value);
	}
	else
	{
		ft_putendl_fd("filename expected", 1);
		app->parser_error = TRUE;
	}
}

void	parser_handle_argv(t_cmd **cmd, t_token *token)
{
	cmd_append_argv(*cmd, token->value);
	cmd_append_argvtype(*cmd, &(token->type));
}
