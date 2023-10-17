#include "../inc/minishell.h"
#include <stdio.h>
#include <string.h>

void	print_lex_info(t_lex_tok *lex_tok)
{
	int	i;

	i = 0;
	while (lex_tok)
	{
		ft_printf("tok[%d] : %s\n type : ", i, lex_tok->token);
		if (lex_tok->type == 0)
			ft_printf("LESS\n");
		else if (lex_tok->type == 1)
			ft_printf("GREAT\n");
		else if (lex_tok->type == 2)
			ft_printf("GG\n");
		else if (lex_tok->type == 3)
			ft_printf("LL\n");
		else if (lex_tok->type == 4)
			ft_printf("PIPE\n");
		else if (lex_tok->type == 5)
			ft_printf("WORD\n");
		else if (lex_tok->type == 6)
			ft_printf("ERRORL\n");
		else if (lex_tok->type == 7)
			ft_printf("DOLLARS\n");
		else if (lex_tok->type == 8)
			ft_printf("LIMITER\n");
		else if (lex_tok->type == 9)
			ft_printf("RESERVED\n");
		else if (lex_tok->type == 10)
			ft_printf("INDEFINE\n");
		else if (lex_tok->type == 11)
			ft_printf("INFILE\n");
		lex_tok = lex_tok->next;
		i++;
	}
}

int	main(void)
{
	t_lex_tok *lex_tok;
	char *str;

	while (1)
	{
		lex_tok = NULL;
		str = readline("zebishell> ");
		if (str)
		{
			token_maker(str, &lex_tok);
			if (error_handler(&lex_tok))
				ft_printf("error\n");
			else
			{
				print_lex_info(lex_tok);
				free_struc(lex_tok);
			}
			free(str);
		}
	}
}