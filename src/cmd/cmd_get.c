/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 21:09:24 by smoroz            #+#    #+#             */
/*   Updated: 2024/04/16 09:00:17 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cmd.h"

char	*cmd_argv_at(t_cmd *cmd, int i)
{
	return (darray_get_at(&(cmd->argv), i));
}

char	*cmd_redir_at(t_cmd *cmd, int i)
{
	return (darray_get_at(&(cmd->redir), i));
}

int	cmd_argtype_at(t_cmd *cmd, int i)
{
	return (*(int *)darray_get_at(&(cmd->argvtype), i));
}

void	cmd_set_argtype_at(t_cmd *cmd, int i, int val)
{
	*(int *)darray_get_at(&(cmd->argvtype), i) = val;
}

void	cmd_set_argv_at(t_cmd *cmd, int i, void *s)
{
	t_darr	*argv;

	argv = &(cmd->argv);
	*(argv->content + i) = s;
}
