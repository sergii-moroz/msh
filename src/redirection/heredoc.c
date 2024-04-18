/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:55:55 by smoroz            #+#    #+#             */
/*   Updated: 2024/04/16 14:55:55 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/redirection.h"

static void hdoc_print_fd(t_darr *darr, int fd)
{
	int	i;

	i = 0;
	while (i < darr->count)
	{
		ft_putendl_fd(darr->content[i], fd);
		i++;
	}
}

static void	ft_heredoc(char *end, int *fd)
{
	char	*line;
	t_darr	hdoc;

	darray_init(&hdoc);
	close(fd[0]);
	while(1)
	{
		line = readline("heredoc -> ");
		if (!ft_strncmp(line, end, ft_strlen(end) + 1))
		{
			free(line);
			line = NULL;
			dup2(fd[1], 1);//
			close(fd[1]);
			hdoc_print_fd(&hdoc, 1);
			darray_del_all(&hdoc);
			exit(EXIT_SUCCESS);
		}
		if (line && *line)
		{
			darray_append(&hdoc, line);
		}
	}
}

void	sub_process_herdoc(char *end, char *cmd_name)
{
	pid_t	pid;
	int		fd[2];
	int		in;

	in = dup(STDIN_FILENO);
	pipe(fd);
	pid = fork();
	if (is_fork_error(pid))
	{
		perror("fork: failed");
		exit(1);
	}
	else if (is_child(pid))
	{
		ft_heredoc(end, fd);
	}
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
	printf("before wait...\n");
	waitpid(pid, NULL, 0);
	printf("after wait...\n");
	if (is_builtin(cmd_name))
		dup2(in, 0);
	//darray_print_string_row(redir);
	printf("END heredoc\n");
}

void	ft_handle_heredoc(t_cmd *cmd)
{
	t_darr	*redir;
	int		i;
	char	*end, *cmd_name;

	redir = &cmd->redir;
	i = 0;
	while (i < redir->count)
	{
		if (!ft_strncmp(darray_get_at(redir, i), "<<", 3))
		{
			i++;
			end = darray_get_at(redir, i);
			printf(RED"end: \"%s\"\n"RESET, end);
			//TODO: check for end word. if not set default.
			cmd_name = cmd_argv_at(cmd, 0);
			sub_process_herdoc(end, cmd_name);
		}
		i++;
	}
	printf("exit: handle_heredoc\n");
}
