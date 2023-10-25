/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotvin <dpotvin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:47:30 by dpotvin           #+#    #+#             */
/*   Updated: 2023/08/15 18:29:15 by dpotvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Init the node, here the commands/delimiter are split by strtok_monkas
static void	init_node(t_input *newNode, char *token)
{
	int		i;
	int		len;
	char	*commands;

	i = 0;
	len = count_strtok_monkas(token) + 1;
	newNode->commands = ft_calloc(len, sizeof(char *));
	newNode->_stdin = STDIN_FILENO;
	newNode->_stdout = STDOUT_FILENO;
	commands = ft_strtok_monkas(token);
	while (commands && !hstate()->c)
	{
		compute_node(commands, newNode, &i);
		commands = ft_strtok_monkas(0);
	}
	newNode->commands[len - 1] = 0;
}

// Init the next node in the linkedlist / linkedlisthead, to save lines
static void	init_next(t_input **ll, t_input **newnode, t_input **llh)
{
	if (!(*ll))
	{
		*ll = *newnode;
		*llh = *ll;
	}
	else
	{
		(*ll)->next = *newnode;
		*ll = (*ll)->next;
	}
}

// Split the | commands
t_input	*parse_input(char *input, t_input *linkedlist)
{
	char		*token;
	t_input		*newnode;
	t_input		*previousnode;
	t_input		*linkedlisthead;

	linkedlist = NULL;
	previousnode = NULL;
	linkedlisthead = NULL;
	token = ft_strtok(input);
	while (token && !hstate()->c)
	{
		newnode = ft_calloc(sizeof(t_input), 1);
		if (!newnode)
		{
			printf("Malloc error while trying to add Node to LL\n");
			exit(1);
		}
		init_node(newnode, token);
		init_next(&linkedlist, &newnode, &linkedlisthead);
		newnode->previous = previousnode;
		previousnode = newnode;
		token = ft_strtok(NULL);
	}
	free(input);
	return (linkedlisthead);
}
