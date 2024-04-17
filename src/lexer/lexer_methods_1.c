/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_methods.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:45:25 by smoroz            #+#    #+#             */
/*   Updated: 2024/03/31 18:45:25 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static char	*cut_quote(t_lexer_data *data)
{
	int	start;
	int	c;

	c = data->current_char;
	advance(data);
	start = data->i;
	while (data->current_char && data->current_char != c)
		advance(data);
	if (data->current_char != c)
	{
		data->had_error = TRUE;
		error("lexer", "couldn't find closing character");
		return (NULL);
	}
	advance(data);
	return (ft_substr(data->s, start, data->i - start - 1));
}

t_token	*lexer_get_quote(t_lexer_data *data)
{
	t_token	*token;
	int		type;
	char	*str;

	type = QUOTE;
	if (data->current_char == '"')
		type = DQUOTE;
	str = cut_quote(data);
	if (is_null(str, data))
		return (NULL);
	token = token_new(str, type);
	return (token);
}

static char	*cut_word(t_lexer_data *data)
{
	int	start;

	start = data->i;
	while(data->current_char && \
		!is_less_great_or_and(data->current_char) && \
		!is_quote(data->current_char) && \
		!ft_isspace(data->current_char))
		advance(data);
	return (ft_substr(data->s, start, data->i - start));
}

t_token	*lexer_get_word(t_lexer_data *data)
{
	t_token	*token;
	char	*str;

	if (data->current_char == '\0')
		return (NULL);
	str = cut_word(data);
	if (is_null(str, data))
		return (NULL);
	token = token_new(str, WORD);
	return (token);
}

t_token	*lexer_get_parentheses(t_lexer_data *data)
{
	t_token	*token;
	char	*str;
	int		type;

	type = PARE_R;
	if (data->current_char == '(')
		type = PARE_L;
	str = ft_substr(data->s, data->i, 1);
	if (is_null(str, data))
		return (NULL);
	token = token_new(str, type);
	advance(data);
	return (token);
}
