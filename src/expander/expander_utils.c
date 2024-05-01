/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:44:05 by smoroz            #+#    #+#             */
/*   Updated: 2024/04/29 20:19:15 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"

char	*handle_qmark(char *src, char *dest, t_darr *envp, int *start, int *i)
{
	char	*val;

	dest = copy_before(src, dest, *start, *i - *start);
	val = ft_get_env(envp, "?");
	dest = copy_val(dest, val);
	*i += 2;
	*start = *i;
	return (dest);
}

char	*handle_var(char *src, char *dest, t_darr *envp, int *start, int *i)
{
	char	*val;
	char	*key;
	int		j;

	dest = copy_before(src, dest, *start, *i - *start);
	(*i)++;
	*start = *i;
	j = 0;
	while ((src + *i + j) && ft_isalnum(*(src + *i + j)))
		j++;
	key = ft_substr(src, *i, j);
	val = ft_get_env(envp, key);
	free(key);
	dest = copy_val(dest, val);
	*i += j;
	*start = *i;
	return (dest);
}
