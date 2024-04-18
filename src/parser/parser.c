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

static int	parser_peek_type(t_parser_data *data)
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
	t_darr			*cmd_arr;
	t_cmd			*cmd;
	t_token			*token;

	if (!tokens)
		return (NULL);
	//printf("\n=== START PARSER ===\n");
	parser_init(tokens, &data);
	cmd_arr = malloc(sizeof(t_cmd *));
	if (!cmd_arr)
		exit(10);
	darray_init(cmd_arr);
	cmd = malloc(sizeof(t_cmd));
	cmd_init(cmd);
	while (data.current_token)
	{
		token = data.current_token->content;
		//token_print(token);
		if (token->type == WORD || token->type == QUOTE \
			|| token->type == DQUOTE || token->type == SPACES
			|| token->type == NUM)
		{
			cmd_append_argv(cmd, token->value);
			cmd_append_argvtype(cmd, &(token->type));
		}
		else if (token->type == GREAT || token->type == DGREAT \
				|| token->type == LESS || token->type == DLESS)
		{
			cmd_append_redir(cmd, token->value);

			// === io_file ===
			if (parser_peek_type(&data) == SPACES)
				parser_advance(&data);
			if (parser_peek_type(&data) == WORD \
				|| parser_peek_type(&data) == DQUOTE \
				|| parser_peek_type(&data) == QUOTE
				|| parser_peek_type(&data) == NUM)
			{
				parser_advance(&data);
				token = data.current_token->content;
				cmd_append_redir(cmd, token->value);
			}
			else
			{
				ft_putendl_fd("filename expected", 1);
				app->parser_error = TRUE;
				break;
				//exit(1); // TODO: Clean & Exit
			} // end === io_file ===
		}
		else if (token->type == PIPE)
		{
			darray_append(cmd_arr, cmd);
			cmd = malloc(sizeof(t_cmd));
			cmd_init(cmd);
			if (parser_peek_type(&data) == SPACES)
				parser_advance(&data);
		}
		parser_advance(&data);
	}
	if (app->parser_error)
	{
		darray_destroy(cmd_arr);
		return (NULL);
	}
	else
		darray_append(cmd_arr, cmd);

	// parser_print_cmd(cmd_arr);
	//printf("=== END PARSER ===\n\n");
	return (cmd_arr);
}
