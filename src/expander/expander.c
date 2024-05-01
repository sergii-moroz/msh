/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 09:33:37 by smoroz            #+#    #+#             */
/*   Updated: 2024/04/30 07:55:07 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

char	*copy_before(char *src, char *dest, int start, int len)
{
	char	*chunk;
	char	*temp;

	if (!dest)
		dest = ft_substr(src, start, len);
	else
	{
		chunk = ft_substr(src, start, len);
		temp = dest;
		dest = ft_strjoin(temp, chunk);
		free(chunk);
		free(temp);
	}
	return (dest);
}

char	*copy_val(char *dest, char *val)
{
	char	*temp;

	if (!dest)
		dest = val;
	else if (val)
	{
		temp = dest;
		dest = ft_strjoin(temp, val);
		free(temp);
	}
	return (dest);
}

char	*expand_argv(char *s, t_darr *envp)
{
	int		i;
	int		start;
	char	*line;

	line = NULL;
	start = 0;
	i = 0;
	while (s && *(s + i))
	{
		if (*(s + i) == '$' && ft_isalpha(*(s + i + 1)))
			line = handle_var(s, line, envp, &start, &i);
		else if (*(s + i) == '$' && *(s + i + 1) == '?')
			line = handle_qmark(s, line, envp, &start, &i);
		else
			i++;
	}
	line = copy_before(s, line, start, i - start);
	return (line);
}

void	expander(t_cmd *cmd, t_darr *envp)
{
	int		i;
	t_darr	*argv;
	char	*new;

	argv = &(cmd->argv);
	i = 0;
	while (i < argv->count)
	{
		if (cmd_argtype_at(cmd, i) == WORD || cmd_argtype_at(cmd, i) == DQUOTE)
		{
			new = expand_argv(cmd_argv_at(cmd, i), envp); // <- ist verloren gegangen
			//printf("i: %d, old: %s, new: %s\n", i, cmd_argv_at(cmd, i), new);
			cmd_set_argv_at(cmd, i, new); //i think new value remains in argv array && will never freed.
			// have to add to token list; or got through argv and free all that not NULL;
			cmd_set_argtype_at(cmd, i, WORD);
		}
		// else if (cmd_argtype_at(cmd, i) == QUOTE)
		// {
		// 	new = ft_strdup(cmd_argv_at(cmd, i));
		// 	cmd_set_argv_at(cmd, i, new);
		// 	cmd_set_argtype_at(cmd, i, WORD);
		// }
		i++;
	}
}

/*int	main(int argc, char **argv, char **envp)
{
	char *s;
	char	*res;

	s = "[$USER] 10$ [$TEST] [$HOME/$USER.txt]";

	res = expand_argv(s, envp);
	printf("%s\n", res);
	expander(argv, envp);

	int	i = 0;
	while (argv && *(argv + i))
	{
		printf("%s\n", *(argv + i));
		i++;
	}
	return (0);
}*/

// line = handle_var(s, line, envp, &start, &i);
// line = copy_before(s, line, start, i - start);
// i++;
// start = i;
// j = 0;
// while ((s + i + j) && ft_isalnum(*(s + i + j)))
// 	j++;
// key = ft_substr(s, i, j);
// val = ft_get_env(envp, key);
// free(key);
// line = copy_val(line, val);
// i += j;
// start = i;

// line = handle_qmark(s, line, envp, &start, &i);
// line = copy_before(s, line, start, i - start);
// val = ft_get_env(envp, "?");
// line = copy_val(line, val);
// i += 2;
// start = i;
