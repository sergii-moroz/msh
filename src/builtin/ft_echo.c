/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:53:28 by smoroz            #+#    #+#             */
/*   Updated: 2024/04/30 21:07:20 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

static int	arg_is_n(char *s)
{
	if (*s != '-')
		return (0);
	s++;
	while (*s == 'n')
		s++;
	if (*s)
		return (0);
	return (1);
}

static int	print_til_last(t_cmd *cmd, int i)
{
	t_darr	*argv;
	char	*s;

	argv = &cmd->argv;
	while (i < argv->count - 1)
	{
		s = cmd_argv_at(cmd, i);
		ft_putstr_fd(s, 1);
		ft_putchar_fd(' ', 1);
		i++;
	}
	return (i);
}

static int	print_last(t_cmd *cmd, int i)
{
	t_darr	*argv;
	char	*s;

	argv = &cmd->argv;
	if (i < argv->count)
	{
		s = cmd_argv_at(cmd, i);
		ft_putstr_fd(s, 1);
	}
	return (i);
}

int	ft_echo(t_cmd *cmd, t_app *app)
{
	t_darr	*argv;
	char	*s;
	int		i;
	int		print_n;

	print_n = 1;
	argv = &cmd->argv;
	// cmd_join_strnum(cmd);
	// cmd_eat_spaces(cmd);
	i = 1;
	while (i < argv->count)
	{
		s = cmd_argv_at(cmd, i);
		if (arg_is_n(s))
			print_n = 0;
		else
			break ;
		i++;
	}
	i = print_til_last(cmd, i);
	i = print_last(cmd, i);
	if (print_n)
		ft_putchar_fd('\n', 1);
	env_save_exitcode(&app->env, EXIT_SUCCESS);
	return (0);
}
