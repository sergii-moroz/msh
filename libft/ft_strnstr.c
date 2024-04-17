/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olanokhi <olanokhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:12:37 by olanokhi          #+#    #+#             */
/*   Updated: 2023/10/20 17:28:49 by olanokhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
unsigned long	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}*/

char	*ft_strnstr(const char *dest, const char *src, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	src_len;

	i = 0;
	src_len = 0;
	while (src[src_len])
		src_len++;
	if (src_len == 0 || (dest == NULL && len == 0))
		return ((char *)dest);
	while (dest[i] && i < len)
	{
		j = 0;
		if (dest[i] == src[j])
		{
			while (dest[i + j] == src[j] && (i + j) < len && src[j])
				j++;
			if (src_len == j)
				return ((char *)dest + i);
		}
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	printf("ft: %s\n", ft_strnstr(((void *)0), "fake", 3));
	printf("or: %s\n", strnstr(((void *)0), "fake", 3));
	return (0);
}*/