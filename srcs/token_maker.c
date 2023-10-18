#include "../inc/minishell.h"

void	tokenise_single_double(char *ret, int *j)
{
	char	c;

	c = ret[*j];
	*j = *j + 1;
	while (ret[*j] && ret[*j] != c)
		*j = *j + 1;
	if (!ret[*j])
		return ;
	*j = *j + 1;
	return ;
}

char	*ft_strtok(char *str, int *error)
{
	char		*ret;
	static int	i;
	int			j;

	j = 0;
	ret = NULL;
	while (str[i] && ft_strchr(" \t\n\r\v", str[i]))
		i++;
	if (!(str[i]))
		return (i = 0, NULL);
	ret = ft_strdup(str + i);
	if (!ret)
		return (*error = 1, NULL);
	if (ret[j] == '|')
		return (i++, ret[1] = '\0', ret);
	while (ret[j] && ft_strchr("<>$?|", ret[j]))
		j++;
	if (!j)
	{
		while (ret[j] && !ft_strchr(" <>&|*$?", ret[j]))
		{
			if (ret[j] && ft_strchr("\'\"", ret[j]))
				tokenise_single_double(ret, &j);
			else
				j++;
		}
	}
	return (i = j + i, ret[j] = '\0', ret);
}

int	assign_type(char *content, int tok_index)
{
	static int	befor_type;

	if (!ft_strncmp(content, "<", 2))
		return (befor_type = LESS, LESS);
	else if (!ft_strncmp(content, "<<", 3))
		return (befor_type = LESSLESS, LESSLESS);
	else if (!ft_strncmp(content, ">", 2))
		return (befor_type = GREAT, GREAT);
	else if (!ft_strncmp(content, ">>", 3))
		return (befor_type = GREATGREAT, GREATGREAT);
	else if (!ft_strncmp(content, "|", 2))
		return (befor_type = PIPE, PIPE);
	else if (!ft_strncmp(content, "$", 2))
		return (befor_type = DOLLARS, DOLLARS);
	else if (!ft_strncmp(content, "$?", 3))
		return (befor_type = ERRORLVL, ERRORLVL);
	else if (ft_strchr("<>&|*$?", content[0]))
		return (befor_type = INDEFINE, INDEFINE);
	else if (befor_type == LESSLESS && tok_index > 1)
		return (befor_type = LIMITER, LIMITER);
	else if ((befor_type == GREAT || befor_type == GREATGREAT) && tok_index > 1)
		return (befor_type = INFILE, INFILE);
	else if (ft_strchr("\'\"", content[0]))
		return (befor_type = WORD, WORD);
	return (befor_type = WORD, WORD);
}

int	token_maker(char *str, t_lex_tok **lex_tok)
{
	char *content;
	char *tmp;
	t_lex_tok *new;
	int error;
	int tok_index;

	error = 0;
	content = malloc(1);
	tmp = content;
	tok_index = 0;
	while (++tok_index)
	{
		content = ft_strtok(str, &error);
		if (error)
			return (free(tmp), -1);
		else if (content == NULL && error == 0)
			return (free(tmp), 0);
		new = ft_lstnew(content, tok_index);
		if (!new)
			return (free(tmp), -1);
		ft_lstadd_back(lex_tok, new);
	}
	return (0);
}