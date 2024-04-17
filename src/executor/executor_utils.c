/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:13:55 by smoroz            #+#    #+#             */
/*   Updated: 2024/04/17 10:39:11 by smoroz           ###   ########.fr       */
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
	int exit_code;

	exit_code = 0;
	if (WIFEXITED(wstatus))
	{
		exit_code = WEXITSTATUS(wstatus);
		printf("statusCode: %d, wstatus: %d\n", exit_code, wstatus); // TODO: Save status Code to $?
	}
	else if (WIFSIGNALED(wstatus))
	{
		exit_code = WTERMSIG(wstatus);
		printf("signalCode: %d, wstatus: %d\n", exit_code, wstatus); // TODO: Save status Code to $?
	}
	env_save_exitcode(&app->env, exit_code);
	return (exit_code);
}


