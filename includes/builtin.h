/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:56:48 by smoroz            #+#    #+#             */
/*   Updated: 2024/05/06 13:47:24 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdio.h>

# include "cmd.h"
# include "app.h"
# include "env.h"
# include "darray.h"
# include "colors.h"
# include "expander.h"
# include "../libft/libft.h"

int		ft_pwd(t_app *app);
int		ft_env(char **env);
int		ft_cd(t_cmd *cmd, t_app *app);
int		ft_echo(t_cmd *cmd, t_app *app);
int		ft_exit(t_cmd *cmd, t_app *app);
int		ft_export(t_cmd *cmd, t_app *app);
int		ft_unset(t_cmd *cmd, t_app *app);

int		ft_char_index(char *s, int c);

//		builtin_utils.c
int		is_builtin(char *path_name);
int		ft_isvalid_int(char *str);
int		ft_isvalid_identifier(char *s);
void	ft_putstrn_fd(char *s, int n, int fd);

#endif
