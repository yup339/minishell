/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotvin <dpotvin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:47:26 by dpotvin           #+#    #+#             */
/*   Updated: 2023/08/15 18:27:24 by dpotvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Change Ouput and close it if its not the default one
static void	change_output(char *file, t_input *node, bool append)
{
	char	*temp;

	if (node->_stdout == -1 || node->_stdin == -1)
		return ;
	temp = remove_quotes(file);
	if (node->_stdout != STDOUT_FILENO)
		close(node->_stdout);
	if (append)
		node->_stdout = open(temp, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		node->_stdout = open(temp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (node->_stdoutname)
		free(node->_stdoutname);
	node->_stdoutname = ft_strdup(temp);
}

// Change Input and close it if its not the default one
void	change_input(char *file, t_input *node)
{
	char	*temp;

	if (node->_stdout == -1 || node->_stdin == -1)
		return ;
	temp = remove_quotes(file);
	if (node->_stdin != STDIN_FILENO)
		close(node->_stdin);
	node->_stdin = open(temp, O_RDONLY);
	if (node->_stdinname)
		free(node->_stdinname);
	node->_stdinname = ft_strdup(temp);
}

// Apply the redirection
static void	do_redirect(char *type, char *file, t_input *node)
{
	if (!file)
	{
		perror_global("Minishell: ");
		return ;
	}
	if (ft_isredir(type) && ft_isredir_or_pipe(file))
	{
		hstate()->c = true;
		ft_putstr_fd("Minishell: syntax error near unexpected token '",
			STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
		g_last_result = UNEXPECTED_TOKEN_ERROR;
		return ;
	}
	if (!ft_strcmp(type, "<<"))
		heredoc(file, node);
	else if (!ft_strcmp(type, ">>"))
		change_output(file, node, true);
	else if (!ft_strcmp(type, "<"))
		change_input(file, node);
	else if (!ft_strcmp(type, ">"))
		change_output(file, node, false);
}

// Backend for the Redirection and pretty much all
void	compute_node(char *command, t_input *node, int *index)
{
	char	*arg;

	if (ft_isredir(command))
		do_redirect(command, ft_strtok_monkas(0), node);
	else
	{
		arg = convert_all_args(command);
		if (*arg != 0)
			node->commands[(*index)++] = ft_strdup(remove_quotes(arg));
	}
}
