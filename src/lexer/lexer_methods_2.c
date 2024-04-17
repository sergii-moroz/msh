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

static char	*cut_number(t_lexer_data *data)
{
	int	start;

	start = data->i;
	while (data->current_char && ft_isdigit(data->current_char))
		advance(data);
	return (ft_substr(data->s, start, data->i - start));
}

t_token	*lexer_get_number(t_lexer_data *data)
{
	t_token	*token;
	char	*str;

	str = cut_number(data);
	if (is_null(str, data))
		return (NULL);
	token = token_new(str, NUM);
	return (token);
}

static char	peek(t_lexer_data *data)
{
	if (data->current_char)
		return (*(data->s + data->i + 1));
	return (data->current_char);
}

t_token	*lexer_get_legraor(t_lexer_data *data)
{
	t_token	*token;
	char	*str;

	if (data->current_char == peek(data))
	{
		str = ft_substr(data->s, data->i, 2);
		advance(data);
	}
	else
		str = ft_substr(data->s, data->i, 1);
	if (is_null(str, data))
		return (NULL);
	token = token_new(str, 0);
	token_set_type(token);
	advance(data);
	return (token);
}

int	is_null(char *str, t_lexer_data *data)
{
	if (!str)
	{
		data->had_error = TRUE;
		error("lexer", "couldn't copy string");
		return (TRUE);
	}
	return (FALSE);
}
