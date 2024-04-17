/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 20:59:28 by smoroz            #+#    #+#             */
/*   Updated: 2024/03/31 20:59:28 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

void	error(char *where, char *message)
{
	ft_putstr_fd("ERROR: ", 1);
	ft_putstr_fd(where, 1);
	ft_putstr_fd(": ", 1);
	ft_putendl_fd(message, 1);
}
