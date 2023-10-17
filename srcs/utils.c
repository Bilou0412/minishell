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
t_lex_tok	*get_last(t_lex_tok **lex_tok)
{
	t_lex_tok	*tmp;

	tmp = *lex_tok;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}
int	other_type(char *content, int last_type)
{
	if (ft_strchr("\'\"", content[0]))
		return (WORD);
	else if (ft_strchr("<>&|*$?", content[0]))
		return (INDEFINE);
	else if (last_type == LESSLESS)
		return (LIMITER);
	else if (last_type == GREATGREAT)
		return (INFILE);
	return (WORD);
}
t_lex_tok	*ft_lstnew(char *content, int quote_error)
{
	t_lex_tok	*new;
	static int	last_type;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->token = content;
	if (!ft_strncmp(content, "<", 2))
		new->type = LESS;
	else if (!ft_strncmp(content, "<<", 3))
		new->type = LESSLESS;
	else if (!ft_strncmp(content, ">", 2))
		new->type = GREAT;
	else if (!ft_strncmp(content, ">>", 3))
		new->type = GREATGREAT;
	else if (!ft_strncmp(content, "|", 2))
		new->type = PIPE;
	else if (!ft_strncmp(content, "$", 2))
		new->type = DOLLARS;
	else if (!ft_strncmp(content, "$?", 3))
		new->type = ERRORLVL;
	else
		new->type = other_type(content, last_type);
	new->next = NULL;
	return (new->quote_error = quote_error, last_type = new->type, new);
}

int	tokenise_single_double(char *ret, int *j)
{
	char	c;

	c = ret[*j];
	*j = *j + 1;
	while (ret[*j] && ret[*j] != c)
		*j = *j + 1;
	if (!ret[*j])
		return (1);
	return (*j = *j + 1, 0);
}

t_lex_tok	*ft_strtok(char *str)
{
	char		*ret;
	static int	i;
	int			j;
	int			quote_error;

	j = 0;
	quote_error = 0;
	ret = NULL;
	while (str[i] && ft_strchr(" \t\n\r\v", str[i]))
		i++;
	if (!(str[i]))
		return (i = 0, NULL);
	ret = ft_strdup(str + i);
	if (!ret)
		return (NULL);
	while (ret[j] && ft_strchr("<>$?", ret[j]))
		j++;
	if (!j && ret[j] && ft_strchr("&|*$", ret[j]))
		j++;
	if (!j)
	{
		while (ret[j] && !ft_strchr(" <>&|*$?", ret[j]))
		{
			if (ret[j] && ft_strchr("\'\"", ret[j]))
				quote_error = tokenise_single_double(ret, &j);
			else
				j++;
		}
	}
	return (i = j + i, ret[j] = '\0', ft_lstnew(ret, quote_error));
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
		new = ft_strtok(str);
	}
}

int	meta_error(t_lex_tok **lex_tok)
{
	t_lex_tok	*tmp;

	tmp = *lex_tok;
	while (tmp->next)
	{
		if (tmp->type < 4 && tmp->next->type < 4)
			return (printf("1\n"), -1);
		if (tmp->type == PIPE && tmp->next->type == PIPE)
			return (printf("2\n"), -1);
		if (tmp->type == INDEFINE || tmp->next->type == INDEFINE)
			return (printf("3\n"), -1);
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
		return (free_struc(*lex_tok),printf("ok\n"), -1);
	return (0);
}