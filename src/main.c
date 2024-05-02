/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:29:50 by smoroz            #+#    #+#             */
/*   Updated: 2024/05/02 16:42:56 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static void	check_leaks()
// {
// 	system("leaks minishell");
// }

void	line_destroy(char *line)
{
	free(line);
	rl_clear_history();
}

void	handle_sigint(int num)
{
	(void)num;
	//ft_putstr_fd("\b\b\033[K\n", 1);
	ft_putstr_fd("\033[s", 1);
	ft_putstr_fd("\033[u \n", 1);
	//ft_putstr_fd("\033[u\033[K\n", 1);
	//ft_putstr_fd("\033[10C\b\b\033[K\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

#include <signal.h>
int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_app	app;

	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	// atexit(check_leaks);
	(void)argc;
	line = *argv;
	app_init(&app, env);
	while (1)
	{
		line = readline(app.msh_line);
		if (!line)
			break;
		if (*line)
		{
			add_history(line);
			app.tokens = lexer(line);
			if (app.tokens == NULL)
				break;
			// ft_lstiter(app.tokens, token_print);
			parser(app.tokens, &app);

			t_cmd	*cmd;
			int i;
			i = 0;
			while (i < app.cmds.count)
			{
				cmd = darray_get_at(&app.cmds, i);
				expander(cmd, &app.env);
				cmd_join_strnum(cmd);
				cmd_eat_spaces(cmd);
				//cmd_print(cmd);
				i++;
			}

			// parser_print_cmd(&app.cmds);
			// if (app.parser_error)
			// {
			// 	app.parser_error = 0;
			// 	continue;
			// }
			executor(&app);
		}
		free(line);
		ft_lstclear(&app.tokens, token_destroy);
		cmd_clean(&app);
	}
	line_destroy(line);
	app_destroy(&app);
	return (EXIT_SUCCESS);
}
