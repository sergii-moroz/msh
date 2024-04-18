/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:53:28 by smoroz            #+#    #+#             */
/*   Updated: 2024/04/18 13:49:56 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

int	ft_env(char **env)
{
	int		i;
	char	*record;

	i = 0;
	while (env && *(env + i))
	{
		record = *(env + i);
		if (ft_isalpha(*record))
			ft_putendl_fd(record, 1);
		i++;
	}
	return (1);
}
