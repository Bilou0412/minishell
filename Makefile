NAME = parser

CC = gcc

CFLAGS = -g -Werror -Wall -Wextra 

RM = rm -rf

SRCS = 	srcs/utils.c\
		srcs/main.c\
		libft/libft.a\

$(NAME) :
	make all -C libft
	gcc $(CFLAGS)  $(SRCS) -lreadline -o $(NAME)


all : $(NAME)

fclean : clean
	$(RM) $(NAME)
	make fclean -C libft

clean :
	$(RM) $(NAME)
	make clean -C libft

re : fclean all