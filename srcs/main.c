#include "../inc/minishell.h"
#include <stdio.h>
#include <string.h>
char *int_to_enum(int c)
{
	if (c == 0)
		return ("META");
	if(c == 1)
		return ("WORD");
	return (NULL);
}

void print_lex_info(t_lex_tok *lex_tok)
{
	int i;

	i = 0;
	while (lex_tok)
	{
		printf("tok[%d] : %s\n",i , lex_tok->token);
		printf("type : %s\n\n",int_to_enum(lex_tok->type));
		lex_tok = lex_tok->next;
		i++;
	}
}

int	main(void)
{
	char		*str = "cat <<eof >file1 && cat file1 && abc || wc<file1 | cat> file2   ";
	t_lex_tok	*lex_tok;

	lex_tok = NULL;
	ft_tokencollector(str, &lex_tok);
	print_lex_info(lex_tok);
	free_struc(lex_tok);
}