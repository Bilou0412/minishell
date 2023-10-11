#include "../libft/libft.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct s_lex_tok
{
	struct s_lex_tok	*next;
	char				*token;
	int					type;
}						t_lex_tok;

enum					e_lex_type
{
	META,
	WORD,
};

t_lex_tok				*ft_strtok(char *str);
t_lex_tok				*ft_lstnew(char *content);
t_lex_tok				*ft_lstlast(t_lex_tok *lst);
void					ft_tokencollector(char *str, t_lex_tok **lex_tok);
void					ft_lstadd_back(t_lex_tok **lst, t_lex_tok *new);
int						free_struc(t_lex_tok *lex_tok);
