/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:13:55 by smoroz            #+#    #+#             */
/*   Updated: 2024/04/18 13:34:26 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executor.h"

int	is_child(pid_t pid)
{
	return (pid == 0);
}

int	is_fork_error(pid_t pid)
{
	return (pid < 0);
}

int	get_exit_code(int wstatus, t_app *app)
{
	int	exit_code;

	exit_code = 0;
	if (WIFEXITED(wstatus))
		exit_code = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
		exit_code = WTERMSIG(wstatus);
	env_save_exitcode(&app->env, exit_code);
	return (exit_code);
}

void	restore_inout(int in, int out)
{
	dup2(out, 1);
	dup2(in, 0);
}

void	save_inout(int *in, int *out)
{
	*in = dup(0);
	*out = dup(1);
}
