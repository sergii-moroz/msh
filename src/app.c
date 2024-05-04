/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:36:19 by smoroz            #+#    #+#             */
/*   Updated: 2024/04/07 15:36:19 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/app.h"

char	*app_set_msh(char *path)
{
	char	*tmp;
	char	*msh;
	char	*p;

	p = path;
	while (p && *p)
	{
		if (*p == '/')
			msh = p;
		p++;
	}
	tmp = ft_strjoin(MSH, msh + 1);
	msh = ft_strjoin(tmp, ARROW);
	free(tmp);
	return (msh);
}

static void	app_copy_env(char **env, t_app *app)
{
	int	i;

	darray_init(&app->env);
	i = 0;
	while (env && *(env + i))
	{
		darray_append(&app->env, ft_strdup(*(env + i)));
		i++;
	}
	darray_append(&app->env, ft_strdup("?=0"));
	//darray_append(&app->env, ft_strdup("$=0"));
}

void	app_init(t_app *app, char **env)
{
	app_copy_env(env, app);
	app->tokens = NULL;
	app->had_error = FALSE;
	app->path = getcwd(NULL, 0);
	app->msh_line = app_set_msh(app->path);
	app->in = dup(0);
	app->out = dup(1);
	darray_init(&app->cmds);
}

/*int	app_env_update(t_list *envl, char *key, char *value)
{
	if (!value)
		ft_envl_del_record(&envl, key);
	else
		ft_envl_add_record(&envl, key, value);
	return (1);
}*/

int	app_destroy(t_app *app)
{
	//ft_lstclear(&(app->envl), ft_envl_del);
	//rl_clear_history();
	free(app->path);
	free(app->msh_line);
	darray_del_all(&app->env);
	ft_lstclear(&(app->tokens), token_destroy);
	// here destroy app->cmds
	return (1);
}
