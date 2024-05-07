/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:00:34 by smoroz            #+#    #+#             */
/*   Updated: 2024/05/02 13:34:16 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/darray.h"

void	*darray_get_at(t_darr *darr, int i)
{
	if (!darr)
		return (NULL);
	if (darr->content && i < darr->count)
		return (darr->content[i]);
	return (NULL);
}

void	*darray_get_first(t_darr *darr)
{
	if (!darr)
		return (NULL);
	if (darr->content && darr->count > 0)
		return (darr->content[0]);
	return (NULL);
}

void	*darray_get_last(t_darr *darr)
{
	if (!darr)
		return (NULL);
	if (darr->content && darr->count > 0)
		return (darr->content[darr->count - 1]);
	return (NULL);
}
