/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:18:35 by smoroz            #+#    #+#             */
/*   Updated: 2024/04/17 12:47:32 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <sys/wait.h>

# include "app.h"
# include "cmd.h"
# include "env.h"
# include "builtin.h"
# include "redirection.h"

//		executor.c
//static int	is_one_builtin(t_darr *cmds);
void	executor(t_app *app);
void	exec_builtin(t_cmd *cmd, t_app *app);

//executor_utils.c
int		is_child(pid_t pid);
int		is_fork_error(pid_t pid);
int		get_exit_code(int wstatus, t_app *app);

//		executor_child.c
//static void	exec_set_stdin(int fd);
//static void	exec_set_stdout(int fd);
//static void	exec_grandchild(t_darr *cmds, char **envp, int *prev, int i)
void	exec_child(t_app *app);
void	exec_grandchild(int i, int *prev, t_app *app);

//		exec_cmd.c
void	handle_cmd(int i, t_app *app);
char	*get_path2binary(char *str, char *cmd);
void	ft_clean_split(char **split);
char	*ft_get_env(t_darr *env, char *key);

/*# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "envp.h"
# include "builtin.h"

//		executor.c
void	executor(t_darr *cmds, char **envp);
//void	pipe_setup(int *fd, int i);
void	exec_cmd(t_darr *cmds, char **envp, int i);


void	expander(char **argv, int **type, char **envp);
void	eat_spaces(char **argv, int **type);*/

#endif
