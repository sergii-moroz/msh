/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:53:28 by smoroz            #+#    #+#             */
/*   Updated: 2024/04/17 11:09:23 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

static char	*ft_replace_tilda(char *s, char *home)
{
	char	*tmp;
	char	*path;

	if (*s == '~')
	{
		if (*(s + 1) == '/')
			path = ft_strjoin(home, s + 1);
		else
		{
			tmp = ft_strjoin(home, "/");
			path = ft_strjoin(tmp, s + 1);
			free(tmp);
		}
	}
	else
		path = ft_strdup(s);
	return (path);
}

/*int	handle_cd(t_cmd *cmd, t_app *app)
{
	t_darr	*argv;

	argv = &cmd->argv;
	cmd_join_strnum(cmd);
	cmd_eat_spaces(cmd);
	ft_cd(char **path, t_app *app);
}*/

int	ft_cd(t_cmd *cmd, t_app *app)
{
	t_darr	*argv;
	char 	*path;

	argv = &cmd->argv;
	cmd_join_strnum(cmd);
	//darray_print_string_row(argv);
	//darray_print_int_row(&cmd->argvtype);
	cmd_eat_spaces(cmd);
	//darray_print_string_row(argv);
	if (argv->count == 1)
		path = ft_get_env(&app->env, "HOME");
	else if (argv->count > 1)
		path = cmd_argv_at(cmd, 1);
	if (!ft_strlen(path))
	{
		env_save_exitcode(&app->env, EXIT_SUCCESS);
		return (EXIT_SUCCESS);
	}
	path = ft_replace_tilda(path, ft_get_env(&app->env, "HOME"));
	if (chdir(path) == -1)
	{
		ft_putstr_fd(BLACK WHITE_BG"-msh:"WHITE RED_BG" ERROR:"RESET RED" cd ", 2);
		perror(path);
		ft_putstr_fd(RESET, 2);
		env_save_exitcode(&app->env, EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	app->path = getcwd(NULL, 0);
	app->msh_line = app_set_msh(app);
	//change env PWD
	env_save_keyval(&app->env, "PWD", app->path);
	env_save_exitcode(&app->env, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
