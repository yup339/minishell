/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotvin <dpotvin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 03:07:26 by dpotvin           #+#    #+#             */
/*   Updated: 2023/08/20 20:19:50 by dpotvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	argschecker(t_input *LL)
{
	while (LL)
	{
		if (!LL->commands)
		{
			ft_putstr_fd("Minishell: syntax error near unexpected token\n",
				STDERR_FILENO);
			return (false);
		}
		LL = LL->next;
	}
	return (true);
}

bool	check_fd(t_input *input)
{
	if (input->_stdin == -1 || input->_stdout == -1)
	{
		if (input->_stdin == -1)
		{
			access(input->_stdinname, R_OK);
			ft_putstr_fd("Minishell: ", STDERR_FILENO);
			perror_global(input->_stdinname);
		}
		if (input->_stdout == -1)
		{
			access(input->_stdoutname, W_OK);
			ft_putstr_fd("Minishell: ", STDERR_FILENO);
			perror_global(input->_stdoutname);
		}
		return (false);
	}
	return (true);
}

bool	check_input(char *input)
{
	int	i;

	i = 0;
	while (ft_isspace(input[i]))
		i++;
	if (input[i] == '|')
	{
		ft_putstr_fd("Minishell: syntax error near unexpected token '|'\n",
			STDERR_FILENO);
		g_last_result = UNEXPECTED_TOKEN_ERROR;
		free(input);
		return (false);
	}
	i = ft_strlen(input) - 1;
	while (ft_isspace(input[i]))
		i--;
	if (input[i] == '|')
	{
		ft_putstr_fd("Minishell: syntax error near unexpected token '|'\n",
			STDERR_FILENO);
		g_last_result = UNEXPECTED_TOKEN_ERROR;
		free(input);
		return (false);
	}
	return (true);
}

void	clean_mess(t_input *LL)
{
	free_input(LL);
	hstate()->c = false;
}

void	restoreline(void)
{
	dup2(hstate()->stdin_clone, STDIN_FILENO);
	close(hstate()->stdin_clone);
	rl_on_new_line();
	rl_redisplay();
	ft_putstr_fd("  \n", 1);
	rl_replace_line("", 0);
}
