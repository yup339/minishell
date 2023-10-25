/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbergero <pascaloubergeron@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 23:33:19 by pbergero          #+#    #+#             */
/*   Updated: 2023/08/09 19:00:03 by pbergero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*free the fd link list */
t_fd_chain	*free_fd_chain(t_fd_chain *fd_chain)
{
	t_fd_chain	*next;

	if (!fd_chain)
		return (NULL);
	next = fd_chain->next;
	free(fd_chain);
	return (free_fd_chain(next));
}

t_fd_chain	*close_fd_chain(t_fd_chain *fd_chain)
{
	t_fd_chain	*next;

	if (!fd_chain)
		return (NULL);
	next = fd_chain->next;
	close(fd_chain->fd[0]);
	close(fd_chain->fd[1]);
	return (close_fd_chain(next));
}

/*create new node for a new link list that contain all the fd's open to create*/
/*the pipeline */
t_fd_chain	*add_new_fd_chain(t_fd_chain *fd_chain)
{
	t_fd_chain	*new_fd;
	t_fd_chain	*tmp;

	new_fd = ft_calloc(1, sizeof(t_fd_chain));
	if (!new_fd)
	{
		perror_global("malloc");
		fd_chain = free_fd_chain(fd_chain);
		return (fd_chain);
	}
	new_fd->next = NULL;
	if (!fd_chain)
	{
		new_fd->previous = NULL;
		return (new_fd);
	}
	tmp = fd_chain;
	while (tmp->next)
		tmp = tmp->next;
	new_fd->previous = tmp;
	tmp->next = new_fd;
	return (fd_chain);
}

/*create new node for a new link list that contain all the fd's open to create*/
/*the pipeline */
t_fd_chain	*open_new_pipe(t_fd_chain *fd_chain)
{
	t_fd_chain	*tmp;

	fd_chain = add_new_fd_chain(fd_chain);
	if (!fd_chain)
		return (NULL);
	tmp = fd_chain;
	while (tmp->next)
		tmp = tmp->next;
	if (pipe(tmp->fd) == -1)
	{
		perror_global("pipe");
		close_fd_chain(fd_chain);
		free_fd_chain(fd_chain);
		return (NULL);
	}
	return (fd_chain);
}
