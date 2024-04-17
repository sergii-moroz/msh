/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:42:14 by smoroz            #+#    #+#             */
/*   Updated: 2024/03/31 18:42:14 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

int	is_less_great_or_and(int c)
{
	if (c == '<' || c == '>' || c == '|' || c == '&')
		return (TRUE);
	return (FALSE);
}

int	is_quote(int c)
{
	if (c == '"' || c == '\'')
		return (TRUE);
	return (FALSE);
}
