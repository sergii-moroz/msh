/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray_del.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 11:34:23 by smoroz            #+#    #+#             */
/*   Updated: 2024/05/02 13:34:20 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/darray.h"

void	darray_del_at(t_darr *darr, int i)
{
	if (i < 0 || i >= darr->count)
		return ;
	ft_memmove(darr->content + i, darr->content + i + 1, \
		(darr->count - i) * sizeof(int *));
	(darr->count)--;
}

void	darray_del_all(t_darr *darr)
{
	int	i;

	if (!darr)
		return ;
	i = 0;
	while (i < darr->count)
	{
		free(darray_get_at(darr, i));
		i++;
	}
	free(darr->content);
}
