/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olanokhi <olanokhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:12:37 by olanokhi          #+#    #+#             */
/*   Updated: 2023/10/20 17:25:42 by olanokhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_int_len(int nb)
{
	int	i;

	i = 1;
	while (nb >= 10)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int nb)
{
	int		m;
	int		nb_len;
	char	*ptr;

	if (nb == -2147483648)
		return (ft_strdup("-2147483648"));
	m = 0;
	if (nb < 0)
	{
		m = 1;
		nb = -nb;
	}
	nb_len = get_int_len(nb);
	ptr = (char *)malloc((nb_len + 1 + m) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	if (m > 0)
		ptr[0] = '-';
	ptr[nb_len + m] = '\0';
	while (nb_len-- > 0)
	{
		ptr[nb_len + m] = nb % 10 + '0';
		nb /= 10;
	}
	return (ptr);
}
