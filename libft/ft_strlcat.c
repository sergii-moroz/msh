/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olanokhi <olanokhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:12:37 by olanokhi          #+#    #+#             */
/*   Updated: 2023/10/20 17:28:19 by olanokhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
unsigned long	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}
*/
unsigned long	ft_strlcat(char *dest, const char *src, unsigned long size)
{
	unsigned long	i;
	unsigned long	dest_len;
	unsigned long	src_len;

	src_len = 0;
	while (src[src_len])
		src_len++;
	if (dest == NULL && size == 0)
		return (src_len);
	dest_len = ft_strlen(dest);
	if (size <= dest_len)
		return (src_len + size);
	i = 0;
	while (dest_len + i < size - 1 && src[i])
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (src_len + dest_len);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	printf("ft: %lu\n", ft_strlcat(((void *)0), "nyan !", 0));
	printf("ft: %lu\n", strlcat(((void *)0), "nyan !", 0));
	return (0);
}*/
