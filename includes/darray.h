/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:58:06 by smoroz            #+#    #+#             */
/*   Updated: 2024/04/30 09:07:03 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DARRAY_H
# define DARRAY_H

# include <stdlib.h>
# include <stdio.h>
# include "colors.h"
# include "../libft/libft.h"

typedef struct s_darr
{
	int		count;
	int		capacity;
	void	**content;
}			t_darr;

//		darray.c
//static int	darray_grow_capacity(int capacity);
void	darray_init(t_darr *darr);
void	darray_append(t_darr *darr, void *content);
void	darray_destroy(t_darr *darr);
void	darray_clean(t_darr *darr);

//		darray_del.c
void	darray_del_at(t_darr *darr, int i);
void	darray_del_all(t_darr *darr);

//		darray_get.c
void	*darray_get_at(t_darr *darr, int i);
void	*darray_get_first(t_darr *darr);
void	*darray_get_last(t_darr *darr);

//		darray_print.c
void	darray_print_string(t_darr *darr);
void	darray_print_string_row(t_darr *darr);
void	darray_print_int_row(t_darr *darr);

#endif
