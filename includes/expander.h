/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 09:32:07 by smoroz            #+#    #+#             */
/*   Updated: 2024/04/29 20:23:50 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "darray.h"
# include "cmd.h"
# include "lexer.h"
# include "executor.h"
# include "../libft/libft.h"

// typedef struct s_exp_data
// {
// 	char	*s;
// 	int		i;
// 	int		start;
// 	char	current_char;
// }			t_exp_data;

//		expander.c
char	*copy_before(char *src, char *dest, int start, int len);
char	*copy_val(char *dest, char *val);
void	expander(t_cmd *cmd, t_darr *env);

//		expander_utils.c
char	*handle_qmark(char *src, char *dest, t_darr *envp, int *start, int *i);
char	*handle_var(char *src, char *dest, t_darr *envp, int *start, int *i);

#endif
