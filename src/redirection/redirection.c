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

	fd = open(name, O_RDONLY);
	dup2(fd, 0);
	close(fd);
}

void	redir_out(char *name)
{
	int	fd;

	fd = open(name, O_CREAT | O_WRONLY | O_TRUNC);
	dup2(fd, 1);
	close(fd);
}

void	redir_append(char *name)
{
	int	fd;

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
