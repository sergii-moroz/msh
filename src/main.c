/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:29:50 by smoroz            #+#    #+#             */
/*   Updated: 2024/04/16 20:59:09 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*line;
	//t_darr	*cmds;
	t_app	app;

	(void)argc;
	line = *argv;
	app_init(&app, env);
	while (1)
	{
		line = readline(app.msh_line);
		if (!ft_strncmp(line, "q", 2) || !ft_strncmp(line, "quit", 5))
		{
			free(line);
			line = NULL;
			//rl_clear_history();
			clear_history();
			break;
		}
		if (line && *line)
		{
			add_history(line);
			// === LEXER ===
			app.tokens = lexer(line);
			ft_lstiter(app.tokens, token_print);
			// === PARSER ==
			app.cmds = parser(app.tokens, &app);
			parser_print_cmd(app.cmds);
			// if (app.parser_error)
			// {
			// 	app.parser_error = 0;
			// 	continue;
			// }
			// === EXECUTOR ===
			executor(&app);
		}
		free(line);
		ft_lstclear(&app.tokens, token_destroy);
	}
	app_destroy(&app);
	return (EXIT_SUCCESS);
}
