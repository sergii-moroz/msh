/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olanokhi <olanokhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:12:37 by olanokhi          #+#    #+#             */
/*   Updated: 2023/10/20 17:28:58 by olanokhi         ###   ########.fr       */
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

char	*ft_strdup(const char *s)
{
	char	*ptr;
	size_t	i;
	size_t	len;

	ptr = NULL;
	i = 0;
	len = 0;
	while (s[len])
	{
		len++;
	}
	ptr = malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	while (i < len)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}*/

unsigned long	get_start(char const *s1, char const *set)
{
	unsigned long	start;
	unsigned long	set_len;
	unsigned long	s1_len;
	unsigned long	i;

	set_len = ft_strlen(set);
	s1_len = ft_strlen(s1);
	start = 0;
	while (start < s1_len)
	{
		i = 0;
		while (i < set_len)
		{
			if (s1[start] == set[i])
			{
				start++;
				break ;
			}
			i++;
		}
		if (i == set_len)
			break ;
	}
	return (start);
}

unsigned long	get_end(char const *s1, char const *set)
{
	unsigned long	end;
	unsigned long	set_len;
	unsigned long	s1_len;
	unsigned long	i;

	set_len = ft_strlen(set);
	s1_len = ft_strlen(s1);
	end = s1_len - 1;
	while (end > 0)
	{
		i = 0;
		while (i < set_len)
		{
			if (s1[end] == set[i])
			{
				end--;
				break ;
			}
			i++;
		}
		if (i == set_len)
			break ;
	}
	return (end + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*ptr;
	unsigned long	i;
	unsigned long	start;
	unsigned long	end;
	unsigned long	len[2];

	start = get_start(s1, set);
	end = get_end(s1, set);
	len[0] = ft_strlen(s1);
	len[1] = ft_strlen(set);
	if (start == len[0])
		return (ft_strdup(""));
	ptr = (char *)malloc((end - start + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < end - start)
	{
		ptr[i] = s1[start + i];
		i++;
	}
	ptr[end - start] = '\0';
	return (ptr);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	*s1;
	char	*s2;
	char	*t;

	s1 = "";
	s2 = "";
	t = ft_strtrim(s1, s2);
	printf("\nft: %p: %s\n", t, t);
	if (t != NULL)
		free(t);
	return (0);
}*/