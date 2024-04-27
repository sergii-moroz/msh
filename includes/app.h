/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:37:50 by smoroz            #+#    #+#             */
/*   Updated: 2024/04/07 15:37:50 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_H
# define APP_H

# include "common.h"
# include "colors.h"
# include "darray.h"
# include "lexer.h"
# include "../libft/libft.h"

typedef struct s_app
{
	t_darr	env;
	int		had_error;
	char	*path;
	char	*msh_line;
	t_list	*tokens;
	t_darr	cmds;
	int		in;
	int		out;
}			t_app;

#define MSH BLACK"msh "RESET
#define ARROW BLACK" » "RESET

void	app_init(t_app *app, char **envp);
int		app_destroy(t_app *app);
char	*app_set_msh(t_app *app);

#endif
