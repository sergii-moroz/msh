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

int	g_code = 0;

// static void	check_leaks()
// {
// 	system("leaks minishell");
// }

void	line_destroy(char *line)
{
	free(line);
	rl_clear_history();
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_app	app;

	// atexit(check_leaks);
	(void)argc;
	line = *argv;
	app_init(&app, env);
	while (1)
	{
		signal_interactive();
		line = readline(app.msh_line);
		if (!line)
			break;
		if (*line)
		{
			signal_noninteractive();
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
