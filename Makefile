NAME		=	minishell

HEADER		=	inc/

LIBFT		=	libft/libft.a

CC			=	gcc

CFLAGS		=	-Werror -Wall -Wextra -g -I $(HEADER)  #-fsanitize=address

SRCS		=	srcs/tokenise/main.c \
				srcs/tokenise/list_utils.c \
				srcs/tokenise/error.c \
				srcs/tokenise/token_maker.c \
				srcs/tokenise/free.c \
				srcs/builtins/echo.c \
				srcs/exec/mini_exec.c \

OBJS		=	$(SRCS:.c=.o)

all			:	$(NAME)

$(NAME)		:	$(OBJS) $(LIBFT) $(HEADER)
				$(CC) $(CFLAGS) $(OBJS) -lreadline -o  $(NAME) $(LIBFT)

$(LIBFT)	:
				make -C ./libft

clean		:
				rm -rf $(OBJS)
				make clean -C ./libft

fclean		:	clean
				rm $(NAME)
				make fclean -C ./libft

re			:	fclean all
