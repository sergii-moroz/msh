/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 21:09:24 by smoroz            #+#    #+#             */
/*   Updated: 2024/04/15 13:43:51 by smoroz           ###   ########.fr       */
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
	darray_destroy(&(cmd->argv));
	darray_destroy(&(cmd->argvtype));
	darray_destroy(&(cmd->redir));
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
