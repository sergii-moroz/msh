/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 21:25:41 by smoroz            #+#    #+#             */
/*   Updated: 2024/04/16 08:41:28 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include "colors.h"
# include "lexer.h"
# include "app.h"
# include "../includes/darray.h"

typedef struct s_cmd
{
	char	*path;
	t_darr	argv;
	t_darr	argvtype;
	t_darr	redir;
}			t_cmd;

//		cmd.c
void	cmd_init(t_cmd *cmd);
void	cmd_destroy(t_cmd	*cmd);
void	cmd_print(t_cmd	*cmd);
t_cmd	*cmd_create(t_app *app);
void	cmd_clean(t_app *app);

//		cmd_append.c
void	cmd_append_argv(t_cmd *cmd, void *argv);
void	cmd_append_argvtype(t_cmd *cmd, void *type);
void	cmd_append_redir(t_cmd *cmd, void *redir);

//		cmd_get.c
char	*cmd_argv_at(t_cmd *cmd, int i);
char	*cmd_redir_at(t_cmd *cmd, int i);
int		cmd_argtype_at(t_cmd *cmd, int i);
void	cmd_set_argtype_at(t_cmd *cmd, int i, int val);
void	cmd_set_argv_at(t_cmd *cmd, int i, void *s);

//		cmd_utils.c
void	cmd_eat_spaces(t_cmd *cmd);
void	cmd_join_strnum(t_cmd *cmd);

#endif
