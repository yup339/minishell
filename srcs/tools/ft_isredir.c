/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isredir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbergero <pascaloubergeron@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:33:24 by dpotvin           #+#    #+#             */
/*   Updated: 2023/08/09 13:26:03 by pbergero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	ft_isredir(char *str)
{
	int		i;
	char	*delimiters[4];

	i = -1;
	delimiters[0] = "<<";
	delimiters[1] = ">>";
	delimiters[2] = "<";
	delimiters[3] = ">";
	while (++i < 4)
	{
		if (!ft_strncmp(str, delimiters[i], ft_strlen(delimiters[i])))
			return (true);
	}
	return (false);
}

bool	ft_isredir_or_pipe(char *str)
{
	int		i;
	char	*delimiters[5];

	i = -1;
	delimiters[0] = "<<";
	delimiters[1] = ">>";
	delimiters[2] = "<";
	delimiters[3] = ">";
	delimiters[4] = "|";
	while (++i < 5)
	{
		if (!ft_strncmp(str, delimiters[i], ft_strlen(delimiters[i])))
			return (true);
	}
	return (false);
}
