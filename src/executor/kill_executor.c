/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:18:04 by smoroz            #+#    #+#             */
/*   Updated: 2024/04/10 08:37:57 by smoroz           ###   ########.fr       */
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

void	executor(t_darr *cmds, char **envp)
{
	pid_t	pid;
	int		wstatus;

	int	save_stdout = STDOUT_FILENO;
	// execute last cmd as child process
	// all other cmds as grandchild process
	pid = fork();
	if (is_fork_error(pid))
	{
		perror("fork: Failed");
		exit(EXIT_FAILURE);
	}
	else if (is_child(pid))
	{
		exec_child(cmds, envp);
	}
	// === PARENT ===
	// Just waiting for the child process
	waitpid(pid, &wstatus, 0);
	dup2(1, 1);
	if (WIFEXITED(wstatus))
	{
		// means program has finished it's execution normally
		// next step to take exit code of subprocess
		int	statusCode = WEXITSTATUS(wstatus);
		printf("statusCode: %d, wstatus: %d\n", statusCode, wstatus); // TODO: Save status Code to $?
	}
	else if (WIFSIGNALED(wstatus))
	{
		// programm has finished it's execution through signal
		int	signalCode = WTERMSIG(wstatus);
		printf("signalCode: %d, wstatus: %d\n", signalCode, wstatus); // TODO: Save status Code to $?
	}
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
