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

void	parser_advance(t_parser_data *data)
{
	if (data->current_token)
		data->current_token = data->current_token->next;
}

void	parser_print_cmd(t_darr *darr)
{
	int	i;

	i = 0;
	if (!darr)
		return ;
	ft_putstr_fd("\n", 1);
	while (darr->content && darr->content[i])
	{
		ft_putstr_fd(BLACK"[ "RESET, 1);
		ft_putnbr_fd(i, 1);
		ft_putstr_fd(BLACK" ] "RESET, 1);
		cmd_print(darr->content[i]);
		i++;
	}
}

int	parser_is_legrd(int type)
{
	if (type == GREAT || type == DGREAT || type == LESS || type == DLESS)
		return (1);
	return (0);
}

int	parser_is_argv(int type)
{
	if (type == WORD || type == QUOTE || type == DQUOTE || \
		type == SPACES || type == NUM)
		return (1);
	return (0);
}
