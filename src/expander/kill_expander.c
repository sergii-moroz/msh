/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 09:33:37 by smoroz            #+#    #+#             */
/*   Updated: 2024/04/15 17:36:19 by smoroz           ###   ########.fr       */
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
		dest= ft_strjoin(temp, chunk);
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

char	*expand_argv(char *s, t_darr *env)
{
	int	i, j;
	int	start;
	char *line, *key, *val;

	line = NULL;
	/*i = 0; start = 0;
	while ((s + i) && *(s + i))
	{
		if (*(s + i) == '$' && ft_isalpha(*(s + i + 1)))
		{
			line = copy_before(s, line, start, i - start);
			i++;
			start = i;
			j = 0;
			while ((s + i + j) && ft_isalnum(*(s + i + j))) // or '_'
				j++;
			key = ft_substr(s, i, j);
			val = getenv(key);
			free(key);
			line = copy_val(line, val);
			i += j;
			start = i;
		}
		else
			i++;
	}
	line = copy_before(s, line, start, i - start);
	free(s);*/
	return (line);
}

void	expander(t_cmd *cmd, t_darr *env)
{
	int	i;
	t_darr	*argv;
	t_darr	*type;
	char	*s;
	char	*temp;

	argv = &(cmd->argv);
	type = &(cmd->argvtype);
	i = 0;
	//while (argv && *(argv + i))
	while (i < argv->count)
	{
		s = darray_get_at(argv, i);
		//if (**(type + i) == WORD || **(type + i) == DQUOTE)
		printf("type: %d\n", *(int *)darray_get_at(type, i));
		if (*(int *)darray_get_at(type, i) == WORD || *(int *)darray_get_at(type, i) == DQUOTE)
		{
			temp = expand_argv(s, env);
			printf("temp: %s\n", temp);
			//*(argv + i) = expand_argv(*(argv + i), envp);
			//**(type + i) = WORD;
		}
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

/*void	eat_spaces(char **argv, int **type)
{
	int	i;
	t_darr	*new;

	new = malloc(sizeof(t_darr));
	darray_init(new);
	i = 0;
	while (argv && *(argv + i))
	{
		if (**(type + i) == WORD)
			darray_append(new, *(argv + i));
		i++;
	}
	printf("eat space\n");
	darray_print_string_row(new);
}*/
