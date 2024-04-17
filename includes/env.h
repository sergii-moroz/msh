/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 08:40:49 by smoroz            #+#    #+#             */
/*   Updated: 2024/04/17 11:07:28 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "darray.h"
# include "builtin.h"
# include "../libft/libft.h"

void	env_save_exitcode(t_darr *env, int exitcode);
void	env_save_keyval(t_darr *env, char *key, char *val);
int		env_key_index(t_darr *env, char *key, int n);
char	*ft_get_env(t_darr *env, char *key);

#endif
