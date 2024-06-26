/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 17:43:31 by smoroz            #+#    #+#             */
/*   Updated: 2024/04/01 17:43:31 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

int	parser_peek_type(t_parser_data *data)
{
	t_list	*node;
	t_token	*token;

	if (data->current_token)
	{
		node = data->current_token->next;
		if (node)
		{
			token = node->content;
			return (token->type);
		}
	}
	return (-1);
}

void	parser(t_list *tokens, t_app *app)
{
	t_parser_data	data;
	t_cmd			*cmd;
	t_token			*token;

	if (!tokens)
		return ;
	data.current_token = tokens;
	darray_init(&app->cmds);
	cmd = cmd_create(app);
	if (!cmd)
		return ;
	while (data.current_token && !app->had_error)
	{
		token = data.current_token->content;
		if (parser_is_argv(token->type))
			parser_handle_argv(&cmd, token);
		else if (parser_is_legrd(token->type))
			handle_redir(&cmd, token->value, &data, app);
		else if (token->type == PIPE)
			cmd = parser_handle_pipe(app, cmd, &data);
		parser_advance(&data);
	}
	darray_append(&app->cmds, cmd);
	check_syntax_error(cmd, app);
}

void	check_syntax_error(t_cmd *cmd, t_app *app)
{
	if (cmd->argv.count == 0 && cmd->redir.count == 0 && !app->had_error)
	{
		ft_putstr_fd(RED"-msh: syntax error\n"RESET, 2);
		app->had_error = TRUE;
	}
}
