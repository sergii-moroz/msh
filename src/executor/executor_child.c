/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 12:35:44 by smoroz            #+#    #+#             */
/*   Updated: 2024/04/07 12:35:44 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executor.h"

static void	set_stdin(int fd)
{
	if (fd != STDIN_FILENO)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

static void	set_stdout(int fd)
{
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	exec_child(t_app *app)
{
	int	i;
	int	prev;

	prev = STDIN_FILENO;
	i = 0;
	while (i < (app->cmds)->count - 1)
	{
		//printf("      === [ %d ] exec cmd:\n", i);
		exec_grandchild(i, &prev, app);
		i++;
	}
	// wait for grandchild before execute last cmd?????
	//printf("   === [ %d ] exec :\n", i);
	//darray_print_string_row(&(app->env)); //print
	set_stdin(prev);
	handle_cmd(i, app);
}

void	exec_grandchild(int i, int *prev, t_app *app)
{
	pid_t	pid_grand;
	int		fd[2];

	pipe(fd);
	pid_grand = fork();
	if (is_fork_error(pid_grand))
	{
		perror("fork: failed");
		exit(EXIT_FAILURE);
	}
	else if (is_child(pid_grand))
	{
		//printf("       before handle cmd\n");
		set_stdin(*prev);
		//dup2(app->out, 1);
		set_stdout(fd[1]);
		handle_cmd(i, app);
	}
	//printf("      === waiting grandchild pid: %d ===\n", pid_grand);
	waitpid(pid_grand, NULL, 0); //works with and without watpid
	//printf("      === exited grandchild pid: %d ===\n", pid_grand);
	close(*prev);
	close(fd[1]);
	*prev = fd[0];
}
