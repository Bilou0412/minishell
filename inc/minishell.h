#include "../libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

typedef struct s_lex_tok
{
	struct s_lex_tok	*next;
	char				*token;
	int					type;
	int					quote_error;
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
	INFILE,
};

t_lex_tok				*ft_lstnew(char *content, int tok_index);
int						free_struc(t_lex_tok *lex_tok);
int						error_handler(t_lex_tok **lex_tok);
t_lex_tok				*get_last(t_lex_tok **lex_tok);
void					ft_lstadd_back(t_lex_tok **lex_tok, t_lex_tok *new);
int						token_maker(char *str, t_lex_tok **lex_tok);
int						assign_type(char *content, int tok_index);
int						free_struc(t_lex_tok *lex_tok);
int						error_quote(char *content);
int						echo(char *option, char *string);
int						mini_exec(t_lex_tok **lex_tok);
