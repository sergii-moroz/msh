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
		//return ;
		exit(1);// Maybe just return
	}
}

void	redir_out(char *name)
{
	int	fd;
	struct stat buf;

	lstat(name, &buf);
	if(S_ISDIR(buf.st_mode))
	{
		//printf(RED"  directory  "RESET);
		exit(126);
	}
	//printf("File\n");
	fd = open(name, O_CREAT | O_WRONLY | O_TRUNC);
	dup2(fd, 1);
	close(fd);
}

void	redir_append(char *name)
{
	int	fd;
	struct stat buf;

	lstat(name, &buf);
	if(S_ISDIR(buf.st_mode))
	{
		exit(126);
	}
	fd = open(name, O_CREAT | O_WRONLY | O_APPEND);
	dup2(fd, 1);
	close(fd);
}

void	ft_handle_redirection(t_cmd *cmd)
{
	t_darr	*redir;
	int		i;
	int		mod;
	int		fd;
	char	*name;

	redir = &cmd->redir;
	mod = -1;
	i = 0;
	while (i < redir->count)
	{
		if (!ft_strncmp(darray_get_at(redir, i), ">", 2))
		{
			i++;
			name = darray_get_at(redir, i);
			redir_out(name);
		}
			// mod = O_CREAT | O_WRONLY | O_TRUNC;
		else if (!ft_strncmp(darray_get_at(redir, i), ">>", 3))
		{
			i++;
			name = darray_get_at(redir, i);
			redir_append(name);
		}
			// mod = O_CREAT | O_WRONLY | O_APPEND;
		else if (!ft_strncmp(darray_get_at(redir, i), "<", 3))
		{
			i++;
			name = darray_get_at(redir, i);
			redir_in(name);
		}
		// if (mod > 0)
		// {
		// 	i++;
		// 	fd = open(darray_get_at(redir, i), mod);
		// 	dup2(fd, 1);
		// 	close(fd);
		// }
		i++;
	}
}
