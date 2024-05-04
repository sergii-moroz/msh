/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:53:28 by smoroz            #+#    #+#             */
/*   Updated: 2024/05/02 14:54:07 by smoroz           ###   ########.fr       */
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

static int	cd_error(char *path, t_app *app)
{
	ft_putstr_fd(BLACK"-msh:"RED" ERROR: cd ", 2);
	perror(path);
	ft_putstr_fd(RESET, 2);
	env_save_exitcode(&app->env, EXIT_FAILURE);
	free(path);
	return (EXIT_FAILURE);
}

// static int	cd_error_too_many(t_app *app)
// {
// 	ft_putendl_fd(BLACK "-msh:"RED" cd: too many arguments"RESET, 2);
// 	env_save_exitcode(&app->env, EXIT_FAILURE);
// 	return (EXIT_FAILURE);
// }

int	ft_cd(t_cmd *cmd, t_app *app)
{
	t_darr	*argv;
	char	*path;

	argv = &cmd->argv;
	// cmd_join_strnum(cmd);
	// cmd_eat_spaces(cmd);
	if (argv->count == 1)
		path = ft_get_env(&app->env, "HOME");
	//else if (argv->count > 2)
	//	return (cd_error_too_many(app));
	else if (argv->count >= 2)
		path = cmd_argv_at(cmd, 1);
	if (!ft_strlen(path))
	{
		env_save_exitcode(&app->env, EXIT_SUCCESS);
		return (EXIT_SUCCESS);
	}
	path = ft_replace_tilda(path, ft_get_env(&app->env, "HOME"));
	if (chdir(path) == -1)
		return (cd_error(path, app));
	free(path);
	free(app->path);
	app->path = getcwd(NULL, 0);
	free(app->msh_line);
	app->msh_line = app_set_msh(app->path);
	env_save_keyval(&app->env, "PWD", app->path);
	env_save_exitcode(&app->env, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
