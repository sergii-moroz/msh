/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 08:41:04 by smoroz            #+#    #+#             */
/*   Updated: 2024/04/18 15:53:53 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executor.h"

static int	is_one_builtin(t_darr *cmds)
{
	t_cmd	*cmd;
	char	*cmd_name;

	if (cmds->count == 1)
	{
		cmd = darray_get_first(cmds);
		cmd_name = cmd_argv_at(cmd, 0);
		if (is_builtin(cmd_name))
			return (TRUE);
		else
			return (FALSE);
	}
	return (FALSE);
}

void	exec_builtin(t_cmd *cmd, t_app *app)
{
	char	*cmd_name;
	int		in;
	int		out;

	in = dup(0);
	out = dup(1);
	expander(cmd, &app->env);
	//ft_handle_heredoc(cmd);
	ft_handle_redirection(cmd);
	cmd_name = cmd_argv_at(cmd, 0);
	if (!ft_strncmp(cmd_name, "cd", 3))
		ft_cd(cmd, app);
	else if (!ft_strncmp(cmd_name, "pwd", 4))
		ft_pwd(app);
	else if (!ft_strncmp(cmd_name, "env", 4))
		ft_env((char **)app->env.content);
	else if (!ft_strncmp(cmd_name, "exit", 5))
		ft_exit(cmd, app);
	else if (!ft_strncmp(cmd_name, "echo", 5))
		ft_echo(cmd, app);
	else if (!ft_strncmp(cmd_name, "unset", 6))
		ft_unset(cmd, app);
	else if (!ft_strncmp(cmd_name, "export", 7))
		ft_export(cmd, app);
	dup2(out, 1);
	dup2(in, 0);
}

void	exec_pipe_line(t_app *app)
{
	pid_t	pid;
	int	wstatus;

	//printf("=== fork ===\n");
	pid = fork();
	if (is_fork_error(pid))
	{
		perror("fork: Failed");
		exit(EXIT_FAILURE); //TODO: properly clear & exit
	}
	else if (is_child(pid))
	{
		exec_child(app);
		//printf("child: process:\n");
		exit(0); // move in exec_child_
	}
	//printf("   === waiting child pid: %d ===\n", pid);
	waitpid(pid, &wstatus, 0);
	//printf("   === exited child pid: %d ===\n", pid);
	get_exit_code(wstatus, app);
	//printf("many command\n");
}

void	executor(t_app *app)
{
	if (is_one_builtin(app->cmds))
		exec_builtin(darray_get_first(app->cmds), app);
	else
		exec_pipe_line(app);
}
