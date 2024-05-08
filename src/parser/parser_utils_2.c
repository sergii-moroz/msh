/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:38:04 by olanokhi          #+#    #+#             */
/*   Updated: 2024/05/06 13:51:07 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

t_cmd	*parser_handle_pipe(t_app *app, t_cmd *cmd, t_parser_data *data)
{
	darray_append(&app->cmds, cmd);
	if (cmd->argv.count == 0 && cmd->redir.count == 0 && !app->had_error)
	{
		ft_putstr_fd(RED"-msh: syntax error\n"RESET, 2);
		app->had_error = TRUE;
	}
	cmd = cmd_create(app);
	if (!cmd)
		return (NULL);
	if (parser_peek_type(data) == SPACES)
		parser_advance(data);
	return (cmd);
}

void	handle_redir(t_cmd **cmd, char *value, t_parser_data *data, t_app *app)
{
	t_token	*token;

	cmd_append_redir(*cmd, ft_strdup(value));
	if (parser_peek_type(data) == SPACES)
		parser_advance(data);
	if (parser_peek_type(data) == WORD \
		|| parser_peek_type(data) == DQUOTE \
		|| parser_peek_type(data) == QUOTE
		|| parser_peek_type(data) == NUM)
	{
		parser_advance(data);
		token = data->current_token->content;
		cmd_append_redir(*cmd, ft_strdup(token->value));
	}
	else
	{
		ft_putendl_fd("filename expected: default filename \"empty.txt\"", 1);
		app->had_error = TRUE;
	}
}

void	parser_handle_argv(t_cmd **cmd, t_token *token)
{
	cmd_append_argv(*cmd, ft_strdup(token->value));
	cmd_append_argvtype(*cmd, &(token->type));
}
