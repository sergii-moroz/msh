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

static void	hdoc_print_fd(t_darr *darr, int fd)
{
	int	i;

	i = 0;
	while (i < darr->count)
	{
		ft_putendl_fd(darr->content[i], fd);
		i++;
	}
}

static t_darr	heredoc_read(char *end)
{
	char	*line;
	t_darr	hdoc;

	darray_init(&hdoc);
	while (1)
	{
		line = readline(BLUE"heredoc"ARROW RESET);
		if (!ft_strncmp(line, end, ft_strlen(end) + 1))
		{
			free(line);
			return (hdoc);
		}
		if (line && *line)
			darray_append(&hdoc, line);
	}
}

static void	hpipe(t_darr *hdoc)
{
	pid_t	hpid;
	int		hfd[2];

	pipe(hfd);
	hpid = fork();
	if (is_fork_error(hpid))
	{
		perror("fork: failed");
		exit(1);
	}
	else if (is_child(hpid))
	{
		dup2(hfd[1], 1);
		close(hfd[1]);
		close(hfd[0]);
		hdoc_print_fd(hdoc, 1);
		darray_del_all(hdoc);
		exit(EXIT_SUCCESS);
	}
	dup2(hfd[0], 0);
	close(hfd[0]);
	close(hfd[1]);
	waitpid(hpid, NULL, 0);
}

void	handle_heredoc(t_cmd *cmd, t_app *app)
{
	t_darr	*redir;
	int		i;
	char	*end;
	t_darr	hdoc;
	int		oldout;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	oldout = dup(1);
	darray_init(&hdoc);
	redir = &cmd->redir;
	i = 0;
	while (i < redir->count)
	{
		if (!ft_strncmp(darray_get_at(redir, i), "<<", 3))
		{
			dup2(app->in, 0);
			dup2(app->out, 1);
			i++;
			end = darray_get_at(redir, i);
			if (hdoc.count > 0)
				darray_del_all(&hdoc);
			hdoc = heredoc_read(end);
		}
		i++;
	}
	if (hdoc.count > 0)
	{
		dup2(oldout, 1);
		hpipe(&hdoc);
	}
}
