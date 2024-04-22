/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:15:43 by smoroz            #+#    #+#             */
/*   Updated: 2024/04/13 19:32:49 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

void	cmd_eat_spaces(t_cmd *cmd)//t_darr *argv, t_darr *type)
{
	int	i;
	t_darr	*argv;
	t_darr	*type;

	argv = &(cmd->argv);
	type = &(cmd->argvtype);
	i = 0;
	while (i < argv->count)
	{
		if (*(int *)darray_get_at(type, i) == SPACES || ft_strlen(darray_get_at(argv, i)) == 0)
		{
			darray_del_at(argv, i);
			darray_del_at(type, i);
		}
		else
			i++;
	}
}

void	cmd_join_strnum(t_cmd *cmd)
{
	t_darr	*argv;
	t_darr	*type;
	argv = &(cmd->argv);
	type = &(cmd->argvtype);
	int	i;
	int	prev_type;
	int	current_type;
	char	*tmp;

	prev_type = SPACES;
	i = 0;
	while (i < argv->count)
	{
		current_type = *(int *)darray_get_at(type, i);
		//printf("[ %d ] curr: %d, prev: %d\n", i, current_type, prev_type);
		if ((current_type == WORD || current_type == QUOTE || current_type == NUM) \
			&& (prev_type == WORD || prev_type == QUOTE || prev_type == NUM))
		{
			tmp = ft_strjoin(darray_get_at(argv, i - 1), darray_get_at(argv, i));
			free(argv->content[i - 1]);
			argv->content[i - 1] = tmp;
			*(int *)type->content[i - 1] = WORD;
			prev_type = WORD;
			darray_del_at(argv, i);
			darray_del_at(type, i);
		}
		else
		{
			prev_type = current_type;
			i++;
		}
	}
}
