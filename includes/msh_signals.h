/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_signals.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 20:52:23 by smoroz            #+#    #+#             */
/*   Updated: 2024/05/06 13:58:44 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_SIGNALS_H
# define MSH_SIGNALS_H

# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include "app.h"
# include "../libft/libft.h"

extern int	g_code;

void	signal_interactive(void);
void	signal_noninteractive(void);
void	signal_interactive_hdoc(void);

#endif
