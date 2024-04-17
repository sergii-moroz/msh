/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:11:18 by smoroz            #+#    #+#             */
/*   Updated: 2024/04/14 15:11:18 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

static int	ft_unset_del_var(t_darr *env, char *s)
{
	int	key_len;
	int	i;

	if (!ft_isvalid_identifier(s))
	{
		ft_putstr_fd("-bash: "RED"unset: '", 2);
		ft_putstr_fd(s, 2);
		ft_putendl_fd("': not a valid identifier"RESET, 2);
		return (EXIT_FAILURE);
	}
	else
	{
		key_len = ft_strlen(s);
		i = env_key_index(env, s, key_len);
		if (i > 0)
			darray_del_at(env, i);
		return (EXIT_SUCCESS);
	}
}

int	ft_unset(t_cmd *cmd, t_app *app)
{
	t_darr	*argv;
	char	*s;
	int		i;
	int		res;

	argv = &cmd->argv;
	cmd_join_strnum(cmd);
	cmd_eat_spaces(cmd);
	res = 0;
	i = 1;
	while (i < argv->count)
	{
		s = cmd_argv_at(cmd, i);
		res += ft_unset_del_var(&app->env, s);
		i++;
	}
	if (res > 0)
		res = 1;
	//printf(YELLOW"exitCode: %d\n"RESET, res);
	env_save_exitcode(&app->env, res);
	return (res);
}
