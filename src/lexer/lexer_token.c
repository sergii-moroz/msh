/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoroz <smoroz@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:29:08 by smoroz            #+#    #+#             */
/*   Updated: 2024/03/31 16:29:08 by smoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

t_token	*token_new(char *s, int type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		error("token_new", "can't allocate enough memory for t_token");
		return (NULL);
	}
	token->type = type;
	token->value = s;
	return (token);
}

void	token_destroy(void *token)
{
	free(((t_token *)token)->value);
	free(token);
}

void	token_print(void *token)
{
	if (!token)
		return ;
	ft_putstr_fd(MAGENTA"   Token("BLACK" type: "RESET, 1);
	ft_putnbr_fd(((t_token *)token)->type, 1);
	ft_putstr_fd(", "BLACK"value: \""RESET, 1);
	ft_putstr_fd(((t_token *)token)->value, 1);
	ft_putendl_fd(BLACK"\" "MAGENTA")"RESET, 1);
}

void	token_set_type(t_token *token)
{
	/*if (!ft_strncmp(token->value, "||", 3))
		token->type = IF_OR;
	else if (!ft_strncmp(token->value, "&&", 3))
		token->type = IF_AND;
	else */
	if (!ft_strncmp(token->value, ">>", 3))
		token->type = DGREAT;
	else if (!ft_strncmp(token->value, "<<", 3))
		token->type = DLESS;
	else if (!ft_strncmp(token->value, "<", 2))
		token->type = LESS;
	else if (!ft_strncmp(token->value, ">", 2))
		token->type = GREAT;
	else if (!ft_strncmp(token->value, "|", 2))
		token->type = PIPE;
	else if (!ft_strncmp(token->value, "\"", 1))
		token->type = DQUOTE;
	else if (!ft_strncmp(token->value, "\'", 1))
		token->type = QUOTE;
	else
		token->type = WORD;
}
