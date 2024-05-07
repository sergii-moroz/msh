/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:29:50 by smoroz            #+#    #+#             */
/*   Updated: 2024/05/06 15:42:52 by smoroz           ###   ########.fr       */
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

void	app_helper(char *line, t_app *app)
{
	signal_noninteractive();
	add_history(line);
	app->tokens = lexer(line);
	if (app->tokens == NULL)
		return ;
	parser(app->tokens, app);
	expander_wrapper(&app->cmds, &app->env);
	executor(app);
}
// ft_lstiter(app.tokens, token_print);

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_app	app;

	(void)argc;
	line = *argv;
	app_init(&app, env);
	while (1)
	{
		signal_interactive();
		line = readline(app.msh_line);
		if (!line)
		{
			g_code = 1;
			break ;
		}
		if (*line)
			app_helper(line, &app);
		free(line);
		ft_lstclear(&app.tokens, token_destroy);
		cmd_clean(&app);
		app.had_error = FALSE;
	}
	line_destroy(line);
	app_destroy(&app);
	return (g_code);
}
	// atexit(check_leaks);
