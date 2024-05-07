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

static t_darr	heredoc_read(char *end, t_darr *envp)
{
	char	*line;
	char	*new;
	t_darr	hdoc;

	darray_init(&hdoc);
	while (1)
	{
		signal_interactive_hdoc();
		line = readline(BLUE"heredoc"ARROW RESET);
		if (!line || !ft_strncmp(line, end, ft_strlen(end) + 1))
		{
			if (!line)
				g_code = 1;
			free(line);
			return (hdoc);
		}
		if (line && *line)
		{
			new = expand_argv(line, envp);
			darray_append(&hdoc, new);
			free(line);
			//darray_append(&hdoc, line);
		}
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
	darray_del_all(hdoc);
}

static t_darr	get_input_from_hdoc(t_cmd *cmd, t_app *app)
{
	int		i;
	char	*end;
	t_darr	hdoc;
	t_darr	*redir;

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
			hdoc = heredoc_read(end, &app->env);
		}
		i++;
	}
	return (hdoc);
}

void	handle_heredoc(t_cmd *cmd, t_app *app)
{
	t_darr	hdoc;
	int		oldout;

	oldout = dup(1);
	hdoc = get_input_from_hdoc(cmd, app);
	if (g_code != 0)
	{
		if (hdoc.count > 0)
			darray_del_all(&hdoc);
		exit(g_code);
	}
	if (hdoc.count > 0)
	{
		dup2(oldout, 1);
		hpipe(&hdoc);
	}
}
