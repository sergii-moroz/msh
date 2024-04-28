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

void	cmd_eat_spaces(t_cmd *cmd)
{
	int		i;
	t_darr	*argv;
	t_darr	*type;

	argv = &(cmd->argv);
	type = &(cmd->argvtype);
	i = 0;
	while (i < argv->count)
	{
		if (*(int *)darray_get_at(type, i) == SPACES \
			|| ft_strlen(darray_get_at(argv, i)) == 0)
		{
			darray_del_at(argv, i);
			darray_del_at(type, i);
		}
		else
			i++;
	}
}

static int	cmd_isvalid_type(int type)
{
	if (type == WORD || type == QUOTE || type == NUM)
		return (1);
	return (0);
}

static void	cmd_join_helper(t_cmd *cmd, int i, int *prev_type)
{
	char	*tmp;
	t_darr	*argv;
	t_darr	*type;

	argv = &cmd->argv;
	type = &cmd->argvtype;
	tmp = ft_strjoin(darray_get_at(argv, i - 1), \
		darray_get_at(argv, i));
	free(argv->content[i - 1]);
	argv->content[i - 1] = tmp;
	*(int *)type->content[i - 1] = WORD;
	*prev_type = WORD;
	darray_del_at(argv, i);
	darray_del_at(type, i);
}

void	cmd_join_strnum(t_cmd *cmd)
{
	t_darr	*argv;
	t_darr	*type;
	int		i;
	int		prev_type;
	int		current_type;

	argv = &(cmd->argv);
	type = &(cmd->argvtype);
	prev_type = SPACES;
	i = 0;
	while (i < argv->count)
	{
		current_type = *(int *)darray_get_at(type, i);
		if (cmd_isvalid_type(current_type) && cmd_isvalid_type(prev_type))
			cmd_join_helper(cmd, i, &prev_type);
		else
		{
			prev_type = current_type;
			i++;
		}
	}
}
