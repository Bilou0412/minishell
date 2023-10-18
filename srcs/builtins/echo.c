#include "../../inc/minishell.h"
#include <stdio.h>
#include <string.h>

void	print_for_echo(char *str_to_print)
{
	char	c;

	c = 0;
	while (*str_to_print)
	{
		if (ft_strchr("\'\"", *str_to_print) && c == 0)
		{
			c = *str_to_print;
			str_to_print++;
		}
		else if (c != '\0' && c == *str_to_print)
			str_to_print++;
		else
		{
			ft_putchar_fd(*str_to_print, 1);
			str_to_print++;
		}
	}
}
int	check_echo_option(char *option)
{
	int	i;

	i = 0;
	if (!ft_strncmp("-n", option, 2))
	{
		i = i + 2;
		while (option[i] == 'n')
			i++;
		if (option[i] == '\0')
			return (0);
		else if (ft_strncmp(option + i, " - ", 3))
			return (0);
		else
			return (1);
	}
	return (1);
}
int	echo(char *option, char *string)
{
	char *str_to_print;

	str_to_print = NULL;
	if (option == NULL && string == NULL)
		ft_putchar_fd('\n', 1);
	else if (!option)
	{
		print_for_echo(string);
		ft_putchar_fd('\n', 1);
	}
	else if (!string)
	{
		if(!check_echo_option(option))
	}
	else if (!check_echo_option(option))
		print_for_echo(string);
	else if (check_echo_option(option) == 1)
	{
		str_to_print = ft_strjoin(option, string);
		if (!str_to_print)
			return (0);
		print_for_echo(str_to_print);
		ft_putchar_fd('\n', 1);
	}
	else if (check_echo_option(option) == 2)
	{
		str_to_print = ft_strjoin(option, string);
		if (!str_to_print)
			return (0);
		print_for_echo(str_to_print + 2);
		ft_putchar_fd('\n', 1);
	}
	if (str_to_print)
		free(str_to_print);
	return (0);
}