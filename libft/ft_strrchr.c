/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olanokhi <olanokhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:12:37 by olanokhi          #+#    #+#             */
/*   Updated: 2023/10/17 16:09:04 by olanokhi         ###   ########.fr       */
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
}
*/
char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	last;

	last = ft_strlen(s);
	i = last - 1;
	if ((char)c == 0)
		return ((char *)s + last);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i--;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	*s1;
	char	*s2;
	int		c;

	s1 = "teste";
	s2 = "teste";
	c = 1024;
	printf("\nst: %p: %s, %i\n", s1, s1, (char)c);
	s1 = ft_strrchr(s1, c);
	printf("\nft: %p: %s\n", s1, s1);
	printf("----------\n");
	s2 = strrchr(s2, c);
	printf("or: %p: %s\n\n", s2, s2);
	return (0);
}*/