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

static char	*cut_spaces(t_lexer_data *data)
{
	int	start;

	start = data->i;
	while (data->current_char && ft_isspace(data->current_char))
		advance(data);
	return (ft_substr(data->s, start, data->i - start));
}

t_token	*lexer_get_spaces(t_lexer_data *data)
{
	t_token	*token;
	char	*str;

	str = cut_spaces(data);
	token = token_new(str, SPACES);
	return (token);
}
