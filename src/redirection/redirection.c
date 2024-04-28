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

void	redir_in(char *name)
{
	int	fd;

	if (access(name, F_OK) == 0)
	{
		fd = open(name, O_RDONLY);
		dup2(fd, 0);
		close(fd);
	}
	else
	{
		ft_putstr_fd(BLACK"-msh: "RESET RED, 2);
		ft_putstr_fd(name, 2);
		ft_putendl_fd(": No such file or directory"RESET, 2);
		exit(1);
	}
}

void	redir_out(char *name)
{
	int			fd;
	struct stat	buf;

	lstat(name, &buf);
	if (S_ISDIR(buf.st_mode))
		exit(126);
	fd = open(name, O_CREAT | O_WRONLY | O_TRUNC);
	if (fd < 0)
	{
		ft_putstr_fd(BLACK"-msh: "RESET RED, 2);
		ft_putstr_fd(name, 2);
		ft_putendl_fd(": Operation not permitted"RESET, 2);
		exit(1);
	}
	dup2(fd, 1);
	close(fd);
}

void	redir_append(char *name)
{
	int			fd;
	struct stat	buf;

	lstat(name, &buf);
	if (S_ISDIR(buf.st_mode))
		exit(126);
	fd = open(name, O_CREAT | O_WRONLY | O_APPEND);
	if (fd < 0)
	{
		ft_putstr_fd(BLACK"-msh: "RESET RED, 2);
		ft_putstr_fd(name, 2);
		ft_putendl_fd(": Operation not permitted"RESET, 2);
		exit(1);
	}
	dup2(fd, 1);
	close(fd);
}

void	ft_handle_redirection(t_cmd *cmd)
{
	t_darr	*redir;
	int		i;
	char	*name;
	char	*s;

	redir = &cmd->redir;
	i = 0;
	while (i < redir->count)
	{
		s = darray_get_at(redir, i);
		if (!ft_strncmp(s, ">", 1) || !ft_strncmp(s, "<", 2))
		{
			i++;
			name = darray_get_at(redir, i);
		}
		if (!ft_strncmp(s, ">", 2))
			redir_out(name);
		else if (!ft_strncmp(s, ">>", 3))
			redir_append(name);
		else if (!ft_strncmp(s, "<", 2))
			redir_in(name);
		i++;
	}
}
