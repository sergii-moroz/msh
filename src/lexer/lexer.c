/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:23:11 by smoroz            #+#    #+#             */
/*   Updated: 2024/03/31 16:23:11 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static void	lexer_init(char *s, t_lexer_data *data)
{
	data->s = s;
	data->i = 0;
	data->had_error = FALSE;
	if (s)
		data->current_char = *s;
}

static void	skip_spaces(t_lexer_data *data)
{
	while (ft_isspace(data->current_char))
		advance(data);
}

void	advance(t_lexer_data *data)
{
	if (data->s && *(data->s + data->i))
	{
		(data->i)++;
		data->current_char = *(data->s + data->i);
	}
}

static t_token	*get_next_token(t_lexer_data *data)
{
	while (data->current_char)
	{
		if (ft_isspace(data->current_char))
			return (lexer_get_spaces(data));
		if (data->current_char == '(' || data->current_char == ')')
			return (lexer_get_parentheses(data));
		else if (is_less_great_or_and(data->current_char))
			return (lexer_get_legraor(data));
		else if (is_quote(data->current_char))
			return (lexer_get_quote(data));
		else if (ft_isdigit(data->current_char))
			return (lexer_get_number(data));
		else
			return (lexer_get_word(data));
		advance(data);
	}
	return (NULL);
}

t_list	*lexer(char *line)
{
	t_lexer_data	data;
	t_list			*tokens;
	t_token			*token;

	tokens = NULL;
	lexer_init(line, &data);
	token = get_next_token(&data);
	while (token)
	{
		ft_lstadd_back(&tokens, ft_lstnew(token));
		token = get_next_token(&data);
	}
	if (data.had_error)
	{
		ft_lstclear(&tokens, token_destroy);
		return (NULL);
	}
	return (tokens);
}
