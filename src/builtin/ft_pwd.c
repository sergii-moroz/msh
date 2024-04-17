/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:53:28 by smoroz            #+#    #+#             */
/*   Updated: 2024/04/17 10:20:37 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

int	ft_pwd(t_app *app)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		perror("error: getcwd");
		env_save_exitcode(&app->env, EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	printf("%s\n", pwd);
	free(pwd);
	env_save_exitcode(&app->env, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
