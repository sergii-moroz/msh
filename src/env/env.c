/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:56:26 by smoroz            #+#    #+#             */
/*   Updated: 2024/04/16 19:56:26 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/env.h"

void	env_save_exitcode(t_darr *env, int exitcode)
{
	int		i;
	char	*key;
	char	*record;
	char	*temp;

	key = "?";
	i = env_key_index(env, key, ft_strlen(key));
	temp = ft_strjoin(key, "=");
	key = ft_itoa(exitcode);
	record = ft_strjoin(temp, key);
	free(temp);
	free(key);
	darray_append(env, record);
	if (i > 0)
	{
		free(darray_get_at(env, i));
		darray_del_at(env, i);
	}
}

void	env_save_keyval(t_darr *env, char *key, char *val)
{
	int		i;
	char	*record;
	char	*temp;

	i = env_key_index(env, key, ft_strlen(key));
	temp = ft_strjoin(key, "=");
	record = ft_strjoin(temp, val);
	free(temp);
	darray_append(env, record);
	if (i > 0)
	{
		free(darray_get_at(env, i));
		darray_del_at(env, i);
	}
}

int	env_key_index(t_darr *env, char *key, int n)
{
	int		i;
	char	*rec;

	i = 0;
	while (i < env->count)
	{
		rec = darray_get_at(env, i);
		if (!ft_strncmp(rec, key, n) \
			&& (*(rec + n) == '\0' || *(rec + n) == '='))
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_get_env(t_darr *env, char *key)
{
	int		i;
	char	*paths;

	i = env_key_index(env, key, ft_strlen(key));
	if (i < 0)
		return (NULL);
	paths = darray_get_at(env, i);
	i = ft_char_index(paths, '=');
	if (i < 0)
		return (NULL);
	return (paths + i + 1);
}
