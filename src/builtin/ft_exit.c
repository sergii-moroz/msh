/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:53:28 by smoroz            #+#    #+#             */
/*   Updated: 2024/04/18 13:43:18 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

int	ft_exit(t_cmd *cmd, t_app *app)
{
	t_darr	*argv;
	char	*exit_code;

	argv = &cmd->argv;
	cmd_join_strnum(cmd);
	cmd_eat_spaces(cmd);
	if (argv->count == 1)
	{
		ft_putendl_fd("exit", 2);
		env_save_exitcode(&app->env, EXIT_SUCCESS);
		exit(EXIT_SUCCESS);
	}
	else if (argv->count == 2)
	{
		exit_code = cmd_argv_at(cmd, 1);
		if (ft_isvalid_int(exit_code))
		{
			ft_putendl_fd("exit", 2);
			env_save_exitcode(&app->env, ft_atoi(exit_code));
			exit(ft_atoi(exit_code));
		}
		else
		{
			ft_putstr_fd("exit\n"RED"-msh: exit: ", 2);
			ft_putstr_fd(exit_code, 2);
			ft_putendl_fd(": numeric argument required"RESET, 2);
			env_save_exitcode(&app->env, 2);
			exit(2);
		}
	}
	else
	{
		ft_putendl_fd("exit\n"RED"-msh: exit: too many arguments"RESET, 2);
		env_save_exitcode(&app->env, EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
}
