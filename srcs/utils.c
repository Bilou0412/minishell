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

t_lex_tok	*ft_lstnew(char *content)
{
	t_lex_tok	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->token = content;
	if (strchr("<>&|*$", content[0]))
		new->type = META;
	else
		new->type = WORD;
	new->next = NULL;
	return (new);
}

t_lex_tok	*ft_strtok(char *str)
{
	char		*ret;
	static char	*s;
	int			i;

	i = 0;
	ret = NULL;
	if (str)
		s = str;
	while (*s && ft_strchr(" \t\n\r\v", *s))
		s++;
	if (!(*s))
		return (NULL);
	ret = ft_strdup(s);
	if (*s && ft_strchr("<>&|*$", *s))
	{
		ret[1] = '\0';
		s++;
		return (ft_lstnew(ret));
	}
	while (*s && !ft_strchr(" <>&|*$", *s))
	{
		i++;
		s++;
	}
	ret[i] = '\0';
	return (ft_lstnew(ret));
}

void	ft_tokencollector(char *str, t_lex_tok **lex_tok)
{
	t_lex_tok	*new;
	t_lex_tok	*tmp;

	new = NULL;
	new = ft_strtok(str);
	while (new)
	{
		if (*lex_tok == NULL)
			*lex_tok = new;
		else
		{
			tmp = *lex_tok;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
		new = ft_strtok(NULL);
	}
}
