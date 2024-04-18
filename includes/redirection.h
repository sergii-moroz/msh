/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:01:03 by smoroz            #+#    #+#             */
/*   Updated: 2024/04/16 15:01:03 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include "cmd.h"
# include "executor.h"

void	ft_handle_redirection(t_cmd *cmd);
void	ft_handle_heredoc(t_cmd *cmd);

#endif
