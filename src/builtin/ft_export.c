/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:53:28 by smoroz            #+#    #+#             */
/*   Updated: 2024/04/18 14:00:34 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

int	ft_char_index(char *s, int c)
{
	int	i;

	i = 0;
	while (s && *(s + i))
	{
		if (*(s + i) == c)
			return (i);
		i++;
	}
	return (-1);
}

static void	ft_export_print_declare(char **envp)
{
	int		i;
	int		eq_pos;
	char	*rec;

	i = 0;
	while (envp && *(envp + i))
	{
		// TODO:	Sort env array
		rec = *(envp + i);
		eq_pos = ft_char_index(*(envp + i), '=');
		ft_putstr_fd(BLACK"declare -x "RESET CYAN, 1);
		if (eq_pos > 0)
		{
			ft_putstrn_fd(rec, eq_pos, 1);
			ft_putstr_fd(RESET BLACK"="RESET BLACK"\""RESET, 1);
			ft_putstr_fd(rec + eq_pos + 1, 1);
			ft_putstr_fd(BLACK"\"", 1);
		}
		else
			ft_putstr_fd(rec, 1);
		ft_putendl_fd(RESET, 1);
		i++;
	}
}

static int	ft_export_add_var(t_darr *env, char *s)
{
	int	pos;
	int	key_len;
	int	i;

	if (!ft_isvalid_identifier(s)) // <- here i check only first character
	{
		ft_putstr_fd("-bash: "RED"export: '", 2);
		ft_putstr_fd(s, 2);
		ft_putendl_fd("': not a valid identifier"RESET, 2);
		return (EXIT_FAILURE);
	}
	else
	{
		pos = ft_char_index(s, '=');
		if (pos < 0)
			key_len = ft_strlen(s);
		else
			key_len = pos;
		i = env_key_index(env, s, key_len);
		if (i < 0)
			darray_append(env, ft_strdup(s));
		if (i >= 0 && pos > 0)
		{
			darray_append(env, ft_strdup(s));
			darray_del_at(env, i);
		}
		//printf(BLUE"env: changed\n"RESET);
		//darray_print_string_row(env);
		return (EXIT_SUCCESS);
	}
}

int	ft_export(t_cmd *cmd, t_app *app)
{
	t_darr	*argv;
	char	*s;
	int		i;
	int		res;

	argv = &cmd->argv;
	cmd_join_strnum(cmd);
	cmd_eat_spaces(cmd);
	//darray_print_string_row(argv);
	if (argv->count == 1)
		ft_export_print_declare((char **)app->env.content);
	res = 0;
	i = 1;
	while (i < argv->count)
	{
		s = cmd_argv_at(cmd, i);
		res += ft_export_add_var(&app->env, s);
		i++;
	}
	if (res > 0)
		res = 1;
	//printf(YELLOW"exitCode: %d\n"RESET, res);
	env_save_exitcode(&app->env, res);
	return (res);
}
