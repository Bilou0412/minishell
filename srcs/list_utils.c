#include "../inc/minishell.h"

t_lex_tok	*get_last(t_lex_tok **lex_tok)
{
	t_lex_tok	*tmp;

	tmp = *lex_tok;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}
t_lex_tok	*ft_lstnew(char *content, int tok_index)
{
	t_lex_tok	*new;

	new = (t_lex_tok *)ft_calloc(1, sizeof(*new));
	if (!new)
		return (NULL);
	new->token = content;
	new->type = assign_type(content, tok_index);
	new->quote_error = error_quote(content);
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back(t_lex_tok **lex_tok, t_lex_tok *new)
{
	t_lex_tok *tmp;

	if (lex_tok)
	{
		if (*lex_tok == NULL)
			*lex_tok = new;
		else
		{
			tmp = get_last(lex_tok);
			tmp->next = new;
		}
	}
}