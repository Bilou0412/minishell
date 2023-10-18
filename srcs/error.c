#include "../inc/minishell.h"

int	error_quote(char *content)
{
	char	c;
	int		error;

	error = 0;
	c = 0;
	while (*content)
	{
		if (ft_strchr("\'\"", *content) && c == 0)
		{
			c = *content;
			error++;
		}
		else if (c != '\0' && c == *content)
			error++;
		content++;
	}
	return (error % 2);
}

int	meta_error(t_lex_tok **lex_tok)
{
	t_lex_tok	*tmp;

	tmp = *lex_tok;
	while (tmp)
	{
		if (tmp->next && tmp->type < 4 && tmp->next->type < 4)
			return (-1);
		if (tmp->next && tmp->type == PIPE && tmp->next->type == PIPE)
			return (-1);
		if (tmp->type == INDEFINE)
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}

int	error_handler(t_lex_tok **lex_tok)
{
	if ((*lex_tok)->type == PIPE)
		return (free_struc(*lex_tok), -1);
	if (get_last(lex_tok)->type <= 4)
		return (free_struc(*lex_tok), -1);
	if (meta_error(lex_tok))
		return (free_struc(*lex_tok), -1);
	if (get_last(lex_tok)->quote_error == 1)
		return (free_struc(*lex_tok), -1);
	return (0);
}