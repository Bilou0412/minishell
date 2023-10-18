#include "../../inc/minishell.h"

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