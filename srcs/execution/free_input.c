/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbergero <pascaloubergeron@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:26:14 by pbergero          #+#    #+#             */
/*   Updated: 2023/08/04 04:58:14 by pbergero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*to free all the allocated memory for the input and  all next input linked*/
void	free_input(t_input *input)
{
	t_input	*tmp;

	if (!input)
		return ;
	while (input && input->previous)
	{
		input = input->previous;
	}
	while (input)
	{
		tmp = input->next;
		close_redirection(input);
		if (input->commands)
			free_double_array((void **)input->commands);
		if (input->_stdoutname)
			free(input->_stdoutname);
		if (input->_stdinname)
			free(input->_stdinname);
		free(input);
		input = tmp;
	}
}
