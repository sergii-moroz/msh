/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:00:34 by smoroz            #+#    #+#             */
/*   Updated: 2024/04/17 13:20:20 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/darray.h"

void	darray_print_string(t_darr *darr)
{
	int	i;

	i = 0;
	while (i < darr->count)
	{
		ft_putstr_fd("[ ", 1);
		ft_putnbr_fd(i, 1);
		ft_putstr_fd(" ] ", 1);
		ft_putendl_fd(darray_get_at(darr, i), 1);
		i++;
	}
}

void	darray_print_string_row(t_darr *darr)
{
	int	i;

	i = 0;
	ft_putstr_fd(BLACK"   count: "RESET, 1);
	ft_putnbr_fd(darr->count, 1);
	ft_putstr_fd(", "BLACK"capacity: "RESET, 1);
	ft_putnbr_fd(darr->capacity, 1);
	ft_putstr_fd(" "MAGENTA"{"RESET, 1);
	while (darr->content && darray_get_at(darr, i))
	{
		ft_putstr_fd(BLACK" \""RESET, 1);
		ft_putstr_fd(darray_get_at(darr, i), 1);
		ft_putstr_fd(BLACK"\""RESET, 1);
		i++;
	}
	ft_putendl_fd(MAGENTA" }"RESET, 1);
}

void	darray_print_int_row(t_darr *darr)
{
	int	i;

	i = 0;
	ft_putstr_fd(BLACK"   count: "RESET, 1);
	ft_putnbr_fd(darr->count, 1);
	ft_putstr_fd(", "BLACK"capacity: "RESET, 1);
	ft_putnbr_fd(darr->capacity, 1);
	ft_putstr_fd(" "MAGENTA"{"RESET, 1);
	while (darr->content && darray_get_at(darr, i))
	{
		ft_putstr_fd(BLACK" \""RESET, 1);
		ft_putnbr_fd(*(int *)darray_get_at(darr, i), 1);
		ft_putstr_fd(BLACK"\""RESET, 1);
		i++;
	}
	ft_putendl_fd(MAGENTA" }"RESET, 1);
}
