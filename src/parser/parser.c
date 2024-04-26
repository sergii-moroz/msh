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

static void	parser_init(t_list *tokens, t_parser_data *data)
{
	data->current_token = tokens;
	data->had_error = FALSE;
}

static t_list	*parser_peek(t_parser_data *data)
{
	if (data->current_token)
		return (data->current_token->next);
	return (NULL);
}

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

t_darr	*parser(t_list *tokens, t_app *app)
{
	t_parser_data	data;
	t_darr			*cmd_arr; // why it is pointer -> rewrite to darray
	t_cmd			*cmd;
	t_token			*token;

	if (!tokens)
		return (NULL);
	parser_init(tokens, &data);
	cmd_arr = malloc(sizeof(t_darr *));
	if (!cmd_arr)
		exit(10); //TODO proper exit
	darray_init(cmd_arr);
	cmd = malloc(sizeof(t_cmd));
	cmd_init(cmd);
	while (data.current_token && !app->parser_error)
	{
		token = data.current_token->content;
		if (parser_is_argv(token->type))
			parser_handle_argv(&cmd, token);
		else if (parser_is_legrd(token->type))
			parser_handle_redir(&cmd, token->value, &data, app);
		else if (token->type == PIPE)
			cmd = parser_handle_pipe(&cmd_arr, cmd, &data);
		parser_advance(&data);
	}
	/* 26.04.2024
	I don't need this block. I could destroy cmds in the app destructor
	if (app->parser_error)
	{
		darray_destroy(cmd_arr); //TODO and destroy cmd
		return (NULL);
	}
	else
	*/
		darray_append(cmd_arr, cmd);
	// parser_print_cmd(cmd_arr);
	return (cmd_arr);
}
