/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_append.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 21:09:24 by smoroz            #+#    #+#             */
/*   Updated: 2024/04/12 08:02:12 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cmd.h"

void	cmd_append_argv(t_cmd *cmd, void *argv)
{
	darray_append(&(cmd->argv), argv);
}

void	cmd_append_argvtype(t_cmd *cmd, void *type)
{
	darray_append(&(cmd->argvtype), type);
}

void	cmd_append_redir(t_cmd *cmd, void *redir)
{
	darray_append(&(cmd->redir), redir);
}
