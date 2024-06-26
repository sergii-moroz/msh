/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 21:09:24 by smoroz            #+#    #+#             */
/*   Updated: 2024/05/06 13:44:11 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cmd.h"

void	cmd_init(t_cmd *cmd)
{
	darray_init(&(cmd->argv));
	darray_init(&(cmd->argvtype));
	darray_init(&(cmd->redir));
}

void	cmd_destroy(t_cmd	*cmd)
{
	darray_clean(&(cmd->argv));
	darray_clean(&(cmd->redir));
	darray_destroy(&(cmd->argvtype));
	free(&(cmd->path));
}

void	cmd_print(t_cmd	*cmd)
{
	ft_putendl_fd("=== cmd ===", 1);
	ft_putstr_fd(CYAN"      ARGV: "RESET, 1);
	darray_print_string_row(&(cmd->argv));
	ft_putstr_fd(CYAN"      TYPE: "RESET, 1);
	darray_print_int_row(&(cmd->argvtype));
	ft_putstr_fd(CYAN"      RDIR: "RESET, 1);
	darray_print_string_row(&(cmd->redir));
}

t_cmd	*cmd_create(t_app *app)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
	{
		app->had_error = TRUE;
		return (NULL);
	}
	cmd_init(cmd);
	return (cmd);
}

void	cmd_clean(t_app *app)
{
	int		i;
	t_darr	*darr;

	darr = &app->cmds;
	if (!darr)
		return ;
	i = 0;
	while (i < darr->count)
	{
		cmd_destroy(darray_get_at(darr, i));
		i++;
	}
	free(darr->content);
	darray_init(darr);
}
