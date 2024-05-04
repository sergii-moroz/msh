/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:43:02 by smoroz            #+#    #+#             */
/*   Updated: 2024/04/25 12:43:12 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/msh_signals.h"

static void	handle_sigint(int num)
{
	char	*tmp;
	char	*msh;

	(void)num;
	tmp = getcwd(NULL, 0);
	msh = app_set_msh(tmp);
	ft_putstr_fd(msh, 1);
	free(tmp);
	free(msh);
	ft_putstr_fd("\033[K\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_interactive(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_noninteractive(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

static void	handle_sigint_hdoc(int num)
{
	(void)num;
	ft_putstr_fd(BLUE"heredoc"ARROW RESET, 1);
	ft_putstr_fd("\033[K\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_interactive_hdoc(void)
{
	signal(SIGINT, handle_sigint_hdoc);
	signal(SIGQUIT, SIG_IGN);
}
