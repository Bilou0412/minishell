#include "../../inc/minishell.h"

char	*get_joined_word(t_lex_tok **lex_tok)
{
	char		*tmp_str;
	char		*tmp_str1;
	t_lex_tok	*tmp;

	tmp = *lex_tok;
	tmp_str1 = ft_strdup(tmp->token);
	ft_printf("ok\n");
	if (!tmp_str1)
		return (NULL);
	while (tmp->type == WORD)
	{
		tmp = tmp->next;
		if (!tmp || tmp->type != WORD)
			break ;
		tmp_str = ft_strjoin(tmp_str1, " ");
		if (!tmp_str1)
			return (NULL);
		free(tmp_str1);
		tmp_str1 = ft_strjoin(tmp_str, tmp->token);
		if (!tmp_str1)
			return (NULL);
		free(tmp_str);
	}
	return (tmp_str1);
}

char	**get_option(t_lex_tok **lex_tok)
{
	char		*option;
	char		*other;
	t_lex_tok	*tmp;
	char		**arg;

	tmp = *lex_tok;
	tmp = tmp->next;
	if (tmp && tmp->token[0] == '-')
	{
		option = ft_strdup(tmp->next->token);
		if (!option)
			return (NULL);
		tmp = tmp->next;
		other = get_joined_word(&tmp);
		if (!other)
			return (NULL);
	}
	else if (tmp)
	{
		option = NULL;
		other = get_joined_word(&tmp);
		if (!other)
			return (NULL);
	}
	arg = malloc(3 * sizeof(char *));
	if (!arg)
		return (NULL);
	arg[0] = option;
	arg[1] = other;
	arg[3] = NULL;
	return (arg);
}

int	mini_exec(t_lex_tok **lex_tok)
{
	t_lex_tok *tmp;
	char **arg;

	arg = ft_split("-nok", ' ');
	ft_print_tab(arg);
	tmp = *lex_tok;
	if (tmp->type == WORD)
	{
		if (!ft_strncmp(tmp->token, "echo\0", 5))
		{
			if (!echo(arg[0], arg[1]))
				return (-1);
		}
	}
	return (0);
}