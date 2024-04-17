/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olanokhi <olanokhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:12:37 by olanokhi          #+#    #+#             */
/*   Updated: 2023/10/20 17:38:49 by olanokhi         ###   ########.fr       */
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*ptr;
	size_t	i;

	s_len = ft_strlen(s);
	ptr = NULL;
	i = 0;
	if (start >= s_len || len == 0)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	ptr = malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	while (i < len)
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strdup(const char *s)
{
	char	*ptr;
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s);
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
}
*/
int	get_split_count(char const *s, char c)
{
	int	i;
	int	w;
	int	count;

	i = 0;
	w = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && w == 0)
		{
			count++;
			w = 1;
		}
		else if (s[i] == c && w == 1)
			w = 0;
		i++;
	}
	return (count);
}

int	get_split_start(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != c)
			return (i);
		i++;
	}
	return (i);
}

int	get_split_len(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (i);
}

char	**free_split(char **str, long n)
{
	while (n >= 0)
		free(str[n--]);
	free(str);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	size_t	start;
	size_t	len;
	size_t	counts[2];
	char	**splited;

	counts[0] = 0;
	if (s != NULL)
		counts[0] = get_split_count(s, c);
	splited = (char **)malloc((counts[0] + 1) * sizeof(char *));
	if (splited == NULL)
		return (NULL);
	counts[1] = 0;
	start = 0;
	while (counts[1] < counts[0])
	{
		start += get_split_start(s + start, c);
		len = get_split_len(s + start, c);
		splited[counts[1]] = ft_substr(s, start, len);
		if (splited[counts[1]] == NULL)
			return (free_split(splited, counts[1]));
		start += len + 1;
		counts[1]++;
	}
	splited[counts[0]] = NULL;
	return (splited);
}
/*
#include <stdio.h>

int	main(void) {
	char	**tab;
	int		i;

	i = 0;
	if (!(tab = ft_split(NULL, 33)))
        printf("NULL");
    else
    {
        while (tab[i] != NULL)
        {
            printf("%i: %s\n", i+1, tab[i]);
            i++;
        }
    }
	return (0);
}
*/