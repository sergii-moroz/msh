/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 09:32:07 by smoroz            #+#    #+#             */
/*   Updated: 2024/04/16 20:03:33 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "darray.h"
# include "cmd.h"
# include "lexer.h"
# include "executor.h"

typedef struct s_exp_data
{
	char	*s;
	int		i;
	int		start;
	char	current_char;
}			t_exp_data;

#include "../libft/libft.h"
#include <stdio.h>

//void	expander(char **argv, int **type, char **envp);
void	expander(t_cmd *cmd, t_darr *env);

#endif
