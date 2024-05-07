/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:18:35 by smoroz            #+#    #+#             */
/*   Updated: 2024/05/02 13:39:08 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <unistd.h>
# include <sys/wait.h>

# include "app.h"
# include "cmd.h"
# include "env.h"
# include "builtin.h"
# include "redirection.h"

//		executor.c
// static int	is_one_builtin(t_darr *cmds);
void	executor(t_app *app);
void	exec_builtin(t_cmd *cmd, t_app *app);
void	exec_pipe_line(t_app *app);

//executor_utils.c
int		is_child(pid_t pid);
int		is_fork_error(pid_t pid);
int		get_exit_code(int wstatus, t_app *app);
void	restore_inout(int in, int out);
void	save_inout(int *in, int *out);

//		executor_child.c
// static void	set_stdin(int fd);
// static void	set_stdout(int fd);
void	exec_child(t_app *app);
void	exec_grandchild(int i, int *prev, t_app *app);

//		handle_cmd.c
// static void	exec_general_cmd(t_cmd *cmd, t_app *app);
void	handle_cmd(int i, t_app *app);
char	*get_path2binary(char *str, char *cmd);
void	ft_clean_split(char **split);

#endif
