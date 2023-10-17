#include "../libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct s_lex_tok
{
	struct s_lex_tok	*next;
	char				*token;
	int					type;
	int					quote;
}						t_lex_tok;

enum					e_token_type
{
	LESS,
	GREAT,
	GREATGREAT,
	LESSLESS,
	PIPE,
	WORD,
	ERRORLVL,
	DOLLARS,
	LIMITER,
	RESERVERDW,
	INDEFINE,
	INFILE
};

t_lex_tok				*ft_strtok(char *str, int *quote);
t_lex_tok				*ft_lstnew(char *content);
t_lex_tok				*ft_lstlast(t_lex_tok *lst);
void					ft_tokencollector(char *str, t_lex_tok **lex_tok);
int						free_struc(t_lex_tok *lex_tok);
int						error_handler(t_lex_tok **lex_tok);
