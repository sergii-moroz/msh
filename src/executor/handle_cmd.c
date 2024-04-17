/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:55:42 by smoroz            #+#    #+#             */
/*   Updated: 2024/04/16 11:55:42 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executor.h"

void	exec_general_cmd(t_cmd *cmd, t_app *app)
{
	char	*env_paths;
	char	**argv;
	char	**envp;

	env_paths = ft_get_env(&app->env, "PATH");
	cmd->path = get_path2binary(env_paths, darray_get_first(&cmd->argv));
	printf("found path: %s\n", cmd->path);
	//darray_print_string_row(&cmd->argv);
	expander(cmd, &app->env);
	cmd_join_strnum(cmd);
	cmd_eat_spaces(cmd);
	//ft_heredoc(cmd);
	//ft_redirection(cmd);
	//darray_print_string_row(&cmd->argv);
	envp = (char **)(app->env).content;
	argv = (char **)(cmd->argv).content;
	execve(cmd->path, argv, envp);
	ft_putendl_fd("-msh: command not found", 1);
	exit(EXIT_FAILURE);
}

void	handle_cmd(int i, t_app *app)
{
	t_cmd	*cmd;

	cmd = darray_get_at(app->cmds, i);
	if (is_builtin(darray_get_first(&cmd->argv)))
	{
		exec_builtin(cmd, app); //TODO: adjust exit code
		exit(0);
	}
	else
		exec_general_cmd(cmd, app);
}

char	*get_path2binary(char *str, char *cmd)
{
	char	**paths;
	char	*cmd_path;
	char	*temp;
	int		i;

	// === check local added 09.04
	if (access(cmd, F_OK) == 0)
		return (cmd);

	i = 0;
	paths = ft_split(str, ':');
	while (paths && *(paths + i))
	{
		temp = ft_strjoin(*(paths + i), "/");
		cmd_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(cmd_path, F_OK) == 0)
		{
			ft_clean_split(paths);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	ft_clean_split(paths);
	return (NULL);
}

void	ft_clean_split(char **split)
{
	int	i;

	i = 0;
	while (split && *(split + i))
	{
		free(*(split + i));
		i++;
	}
	free(split);
	split = NULL;
}
