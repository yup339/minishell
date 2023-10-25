/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbergero <pascaloubergeron@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:53:25 by pbergero          #+#    #+#             */
/*   Updated: 2023/08/06 17:53:11 by pbergero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	is_arg_flag(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (false);
	if (str[1] != 'n')
		return (false);
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

void	print_args(char **args, int i)
{
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
}

/*recreation of echo as a buitin for minishell*/
/*used to print the arg of a t_input*/
void	ms_echo(char **args)
{
	int	i;

	g_last_result = 0;
	if (!args[1])
	{
		printf("\n");
		return ;
	}
	i = 1;
	if (is_arg_flag(args[i]))
	{
		i++;
		print_args(args, i);
	}
	else
	{
		print_args(args, i);
		printf("\n");
	}
}
