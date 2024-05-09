/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:30:32 by smoroz            #+#    #+#             */
/*   Updated: 2024/05/09 15:20:38 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static int	ft_max(char *s1, char *s2)
{
	int	len1;
	int	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 > len2)
		return (len1);
	return (len2);
}

void	env_sort(t_darr *env)
{
	char	*temp;
	int		i;
	int		j;
	int		len;

	if (env->count <= 0)
		return ;
	j = 0;
	while (j < env->count - 1)
	{
		i = 0;
		while (i < env->count - j - 1)
		{
			len = ft_max(env->content[i], env->content[i + 1]);
			if (ft_strncmp(env->content[i], env->content[i + 1], len + 1) > 0)
			{
				temp = env->content[i];
				env->content[i] = env->content[i + 1];
				env->content[i + 1] = temp;
			}
			i++;
		}
		j++;
	}
}

void	env_declare(t_darr *env)
{
	t_darr	temp_env;
	int		i;

	if (!env)
		return ;
	darray_init(&temp_env);
	i = 0;
	while (i < env->count)
	{
		darray_append(&temp_env, ft_strdup(env->content[i]));
		i++;
	}
	env_sort(&temp_env);
	ft_export_print_declare((char **)temp_env.content);
	darray_del_all(&temp_env);
}
