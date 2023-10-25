/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotvin <dpotvin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 00:55:06 by dpotvin           #+#    #+#             */
/*   Updated: 2023/08/15 18:27:24 by dpotvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Hold the Heredoc State
t_hd_state	*hstate(void)
{
	static t_hd_state	t;
	static bool			init;

	if (!init)
	{
		t.stdin_clone = -1;
		init = true;
	}
	return (&t);
}

void	signal_heredok(int sig)
{
	(void)sig;
	g_last_result = EXIT_FAILURE;
	close(STDIN_FILENO);
	hstate()->c = true;
	hstate()->r = true;
}

static void	heredoc2(char **input, char *keyword, int fd)
{
	int	i;

	i = 0;
	signal(SIGINT, signal_heredok);
	signal(SIGQUIT, SIG_IGN);
	hstate()->stdin_clone = dup(STDIN_FILENO);
	while (!hstate()->c && !hstate()->r && ft_strcmp(*input, keyword))
	{
		free(*input);
		*input = readline("> ");
		if (!*input) 
			hstate()->r = true;
		else if (!hstate()->c && ft_strcmp(*input, keyword))
		{
			ft_putstr_fd(convert_all_args_hd(*input), fd);
			ft_putstr_fd("\n", fd);
		}
	}
	if (hstate()->c)
		restoreline();
	else
	{
		close(hstate()->stdin_clone);
		hstate()->stdin_clone = -1;
	}
}

// Heredoc Entry
void	heredoc(char *keyword, t_input *node)
{
	char	*input;
	char	*filename;
	int		fd;

	if (hstate()->fd_broken)
		return ;
	input = malloc(1);
	*input = 0;
	filename = get_uniquefilename();
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	heredoc2(&input, keyword, fd);
	signal(SIGINT, sigint_running_shell);
	close(fd);
	free(input);
	change_input(filename, node);
	if (node->_stdin == -1)
		hstate()->fd_broken = true;
}
