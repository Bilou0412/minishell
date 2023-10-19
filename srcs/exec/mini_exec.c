#include "../../inc/minishell.h"

char	*get_option_echo(t_lex_tok **lex_tok)
{
	char		*option;
	t_lex_tok	*tmp_lst;
	char		*tmp;

	tmp_lst = *lex_tok;
	tmp_lst = tmp_lst->next;
	option = "";
	if (tmp_lst && tmp_lst->token[0] == '-')
	{
		option = ft_strdup(tmp_lst->token);
		if (!option)
			return (NULL);
		tmp_lst = tmp_lst->next;
		while (tmp_lst && tmp_lst->token[0] == '-')
		{
			tmp = ft_strjoin(option, " ");
			free(option);
			if (!tmp)
				return (NULL);
			option = ft_strjoin(tmp, tmp_lst->token);
			if (!option)
				return (NULL);
			tmp_lst = tmp_lst->next;
		}
	}
	return (option);
}
char	*get_str_echo(t_lex_tok **lex_tok)
{
	char		*str;
	t_lex_tok	*tmp_lst;
	char		*tmp;

	tmp_lst = *lex_tok;
	str = "";
	tmp_lst = tmp_lst->next;
	while (tmp_lst && tmp_lst->token[0] == '-')
		tmp_lst = tmp_lst->next;
	if (tmp_lst && tmp_lst->type == WORD)
	{
		str = ft_strdup(tmp_lst->token);
		tmp_lst = tmp_lst->next;
		if(!str)
			return (NULL);
		while(tmp_lst && tmp_lst->type == WORD)
		{
			tmp = ft_strjoin(str, " ");
			free(str);
			if(!tmp)
				return (NULL);
			str = ft_strjoin(tmp, tmp_lst->token);
			free(tmp);
			if(!str)
				return (NULL);
			tmp_lst = tmp_lst->next;
		}
	}
	return (str);
}
char	**get_arg(t_lex_tok **lex_tok)
{
	char		**arg;
	t_lex_tok	*tmp;

	tmp = *lex_tok;
	arg = ft_calloc(3, sizeof(char *));
	if (!arg)
		return (NULL);
	if (!tmp->next || tmp->next->type != WORD)
		return (arg[0] = "", arg[1] = "", arg[2] = NULL, arg);
	return (arg[0] = get_option_echo(lex_tok), arg[1] = get_str_echo(lex_tok),
		arg[2] = NULL, arg);
}

int	mini_exec(t_lex_tok **lex_tok)
{
	t_lex_tok *tmp;
	char **arg;

	tmp = *lex_tok;
	if (tmp->type == WORD)
	{
		if (!ft_strncmp(tmp->token, "echo\0", 5))
		{
			arg = get_arg(lex_tok);
			if (!echo(arg[0], arg[1]))
				return (-1);
		}
	}
	return (0);
}