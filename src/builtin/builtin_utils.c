/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 18:44:50 by smoroz            #+#    #+#             */
/*   Updated: 2024/04/07 18:44:50 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"
#include "../libft/libft.h"

int	is_builtin(char *path_name)
{
	if (!path_name)
		return (0);
	if (!ft_strncmp(path_name, "cd", 3) || \
		!ft_strncmp(path_name, "pwd", 4) || \
		!ft_strncmp(path_name, "env", 4) || \
		!ft_strncmp(path_name, "exit", 5) || \
		!ft_strncmp(path_name, "echo", 5) || \
		!ft_strncmp(path_name, "unset", 6) || \
		!ft_strncmp(path_name, "export", 7))
		return (1);
	return (0);
}

int	ft_isvalid_int(char *str)
{
	if (ft_strlen(str) == 0)
		return (0);
	while (ft_isspace(*str))
		str++;
	if (*str == '\0')
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	if (*str == '\0')
		return (0);
	while (ft_isdigit(*str))
		str++;
	if (*str == '\0')
		return (1);
	return (0);
}

int	ft_isvalid_identifier(char *s)
{
	if (!ft_isalpha(*s) && *s != '_')
		return (0);
	s++;
	while (*s && *s != '=')
	{
		if (!ft_isalnum(*s) && *s != '_')
			return (0);
		s++;
	}
	return (1);
}

void	ft_putstrn_fd(char *s, int n, int fd)
{
	int	i;

	i = 0;
	while (*(s + i) && i < n)
	{
		write(fd, s + i, 1);
		i++;
	}
}
