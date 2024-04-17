/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:00:34 by smoroz            #+#    #+#             */
/*   Updated: 2024/04/17 13:12:11 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/darray.h"

void	darray_init(t_darr *darr)
{
	darr->count = 0;
	darr->capacity = 0;
	darr->content = NULL;
}

static int	darray_grow_capacity(int capacity)
{
	if (capacity < 2)
		return (2);
	else
		return (capacity * 2);
}

void	darray_append(t_darr *darr, void *content)
{
	void	**new;
	int		new_capacity;
	int		size;

	size = sizeof(int *);
	if (darr->count + 2 > darr->capacity)
	{
		new_capacity = darray_grow_capacity(darr->capacity);
		new = malloc(new_capacity * size);
		if (!new)
		{
			perror("couldn't allocate enough memory");
			exit(1); //TODO
		}
		ft_memset(new, 0, new_capacity * size);
		ft_memcpy(new, darr->content, darr->capacity * size);
		free(darr->content);
		darr->capacity = new_capacity;
		darr->content = new;

	}
	darr->content[darr->count] = content;
	darr->count++;
}

void	darray_del_at(t_darr *darr, int i)
{
	if (i < 0 || i >= darr->count)
		return ;
	ft_memmove(darr->content + i, darr->content + i + 1, (darr->count - i) * sizeof(int *));
	(darr->count)--;
}

void	darray_destroy(t_darr *darr)
{
	if (darr->content)
		free(darr->content);
}

void	darray_del_all(t_darr *darr)
{
	int	i;

	i = 0;
	while (i < darr->count)
	{
		free(darray_get_at(darr, i));
		i++;
	}
	free(darr->content);
}
