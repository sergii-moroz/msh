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

static void	ft_heredoc(char *end, int *hfd)
{
	char	*line;
	t_darr	hdoc;

	darray_init(&hdoc);
	while(1)
	{
		line = readline("heredoc -> ");
		if (!ft_strncmp(line, end, ft_strlen(end) + 1))
		{
			free(line);
			line = NULL;
			hdoc_print_fd(&hdoc, hfd[1]);
			darray_del_all(&hdoc);
			close(hfd[1]);
			exit(EXIT_SUCCESS);
		}
		if (line && *line)
		{
			darray_append(&hdoc, line);
		}
	}
}

void	ft_handle_heredoc(t_cmd *cmd)
{
	t_darr	*redir;
	pid_t	pid;
	int		hfd[2];

	redir = &cmd->redir;
	pid = fork();
	if (is_fork_error(pid))
	{
		perror("fork: failed");
		exit(1);
	}
	else if (is_child(pid))
	{
		close(hfd[0]);
		ft_heredoc("END", hfd);
	}

	waitpid(pid, NULL, 0);
	//darray_print_string_row(redir);
	//printf("heredoc\n");
}
