/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbergero <pascaloubergeron@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:30:28 by pbergero          #+#    #+#             */
/*   Updated: 2023/08/20 17:45:57 by pbergero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*make a copy using dup to relink the stdin and the stdout together so readline
	doesnt start to bug and do some craze stuff

The function take as 1 argument thats is define with the e_set_up
	you can ask for multiple option using bit shifting
	
Option: SAVE_PIPE will make a copy of the stdin and stdout this option
will do nothing if the stdin and stdout have already a dup

Option: RESTORE_PIPE will use dup2 to restore the stdin and stdout this option
	should only be use by the main process
	
Option: CLOSE_PIPE will close both the copy of stdin and stdout*/
void	save_std(int option)
{
	static int	save_stdin = -1;
	static int	save_stdout = -1;

	if ((option & SAVE_IN) && save_stdin == -1)
		save_stdin = dup(STDIN_FILENO);
	if ((option & SAVE_OUT) && save_stdout == -1)
		save_stdout = dup(STDOUT_FILENO);
	if (option & RESTORE_IN && save_stdin != -1)
	{
		dup2(save_stdin, STDIN_FILENO);
	}
	if (option & RESTORE_OUT && save_stdout != -1)
		dup2(save_stdout, STDOUT_FILENO);
	if (option & CLOSE_IN && save_stdin != -1)
	{
		close(save_stdin);
		save_stdin = -1;
	}
	if (option & CLOSE_OUT && save_stdout != -1)
	{
		close(save_stdout);
		save_stdout = -1;
	}
}

void	pipeline_error_cleaning(t_input *input, t_fd_chain *fd_chain,
	char	*msg, bool	exiting_process)
{
	if (msg)
		perror_global(msg);
	if (input)
		free_input(input);
	if (fd_chain)
	{
		while (fd_chain->previous)
			fd_chain = fd_chain->previous;
		close_fd_chain(fd_chain);
		free_fd_chain(fd_chain);
	}
	clean_static_memory();
	if (exiting_process)
		exit (g_last_result);
}

void	close_unused_fd(t_fd_chain *fd_chain)
{
	if (!fd_chain)
		return ;
	while (fd_chain->previous)
		fd_chain = fd_chain->previous;
	while (fd_chain)
	{
		close(fd_chain->fd[0]);
		close(fd_chain->fd[1]);
		fd_chain = fd_chain->next;
	}
}

void	close_redirection(t_input *input)
{
	if (input->_stdout != STDOUT_FILENO) 
	{
		close (input->_stdout);
		input->_stdout = STDOUT_FILENO;
	}
	if (input->_stdin != STDIN_FILENO) 
	{
		close (input->_stdin);
		input->_stdout = STDIN_FILENO;
	}
}

void	close_other_redirection_pipe_fd(t_input *input)
{
	t_input	*previous;
	t_input	*next;

	previous = input->previous;
	next = input->next;
	while (next)
	{
		close_redirection(next);
		next = next->next;
	}
	while (previous)
	{
		close_redirection(previous);
		previous = previous->previous;
	}
}
