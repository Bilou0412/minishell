#include "../inc/minishell.h"

int	free_struc(t_lex_tok *lex_tok)
{
	t_lex_tok	*tmp;

	while (lex_tok)
	{
		tmp = lex_tok->next;
		free(lex_tok->token);
		free(lex_tok);
		lex_tok = tmp;
	}
	return (0);
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