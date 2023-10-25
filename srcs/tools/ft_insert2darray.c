/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert2darray.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotvin <dpotvin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:33:11 by dpotvin           #+#    #+#             */
/*   Updated: 2023/07/31 20:54:26 by dpotvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Copy 2d Array and add Newstr
void	ft_insert2darray(char ***dist, char **src, char *newstr)
{
	int		i;
	char	**new;

	new = malloc((ft_count2darray(src) + 2) * sizeof(char *));
	if (!new)
	{
		printf("Malloc error while making new Env\n");
		exit(1);
	}
	i = -1;
	while (src[++i])
	{
		new[i] = ft_strdup(src[i]);
		if (!new[i])
		{
			printf("Malloc error while Copying Env\n");
			exit(1);
		}
	}
	new[i++] = ft_strdup(newstr);
	new[i] = 0;
	*dist = new;
}
