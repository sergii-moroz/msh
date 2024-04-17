/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:53:28 by smoroz            #+#    #+#             */
/*   Updated: 2024/04/17 10:58:18 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

static int arg_is_n(char *s)
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

int	ft_echo(t_cmd *cmd, t_app *app)
{
	t_darr	*argv;
	char	*s;
	int		i;
	int		print_n;

	print_n = 1;
	argv = &cmd->argv;

	//printf("=== before expander\n");
	//darray_print_string_row(argv);
	// DONT WORK expander(cmd, &app->env);
	//printf("=== after expander\n");
	//darray_print_string_row(argv);

	cmd_join_strnum(cmd);
	cmd_eat_spaces(cmd);
	//darray_print_string_row(argv);
	i = 1;
	while (i < argv->count)
	{
		s = cmd_argv_at(cmd, i);
		if (arg_is_n(s))
			print_n = 0;
		else
			break;
		i++;
	}
	while (i < argv->count - 1)
	{
		s = cmd_argv_at(cmd, i);
		ft_putstr_fd(s, 1);
		ft_putchar_fd(' ', 1);
		i++;
	}
	if (i < argv->count)
	{
		s = cmd_argv_at(cmd, i);
		ft_putstr_fd(s, 1);
	}
	if (print_n)
		ft_putchar_fd('\n', 1);
	//printf(YELLOW"exitCode: %d\n"RESET, 0);
	env_save_exitcode(&app->env, EXIT_SUCCESS);
	return (0);
}


