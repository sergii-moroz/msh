/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:44:05 by smoroz            #+#    #+#             */
/*   Updated: 2024/05/06 13:44:24 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"

char	*handle_qmark(char *src, char *dest, t_darr *envp, t_edata *edata)
{
	char	*val;

	dest = copy_before(src, dest, edata->start, edata->i - edata->start);
	val = ft_get_env(envp, "?");
	dest = copy_val(dest, val);
	edata->i += 2;
	edata->start = edata->i;
	return (dest);
}

char	*handle_var(char *src, char *dest, t_darr *envp, t_edata *edata)
{
	char	*val;
	char	*key;
	int		j;

	dest = copy_before(src, dest, edata->start, edata->i - edata->start);
	(edata->i)++;
	edata->start = edata->i;
	j = 0;
	while (src && ft_isalnum(*(src + edata->i + j)))
		j++;
	key = ft_substr(src, edata->i, j);
	val = ft_get_env(envp, key);
	free(key);
	dest = copy_val(dest, val);
	edata->i += j;
	edata->start = edata->i;
	return (dest);
}

void	expander_wrapper(t_darr *cmds, t_darr *env)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	while (i < cmds->count)
	{
		cmd = darray_get_at(cmds, i);
		expander(cmd, env);
		cmd_join_strnum(cmd);
		cmd_eat_spaces(cmd);
		i++;
	}
}
