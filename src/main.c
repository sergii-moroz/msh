/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:29:50 by smoroz            #+#    #+#             */
/*   Updated: 2024/04/26 16:58:27 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	check_leaks()
{
	system("leaks minishell");
}

void	line_destroy(char *line)
{
	free(line);
	rl_clear_history();
}

void	handle_sigint(int num)
{
	(void)num;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	ft_putstr_fd("\n", 1);
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
		/*if (!ft_strncmp(line, "q", 2) || !ft_strncmp(line, "quit", 5))
		{

			break;
		}*/
		if (*line)
		{
			add_history(line);
			app.tokens = lexer(line);
			// ft_lstiter(app.tokens, token_print);
			app.cmds = parser(app.tokens, &app);
			// parser_print_cmd(app.cmds);
			// if (app.parser_error)
			// {
			// 	app.parser_error = 0;
			// 	continue;
			// }
			executor(&app);
		}
		free(line);
		ft_lstclear(&app.tokens, token_destroy);
	}
	line_destroy(line);
	app_destroy(&app);
	return (EXIT_SUCCESS);
}
