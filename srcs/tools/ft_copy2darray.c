/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy2darray.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotvin <dpotvin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:32:57 by dpotvin           #+#    #+#             */
/*   Updated: 2023/07/31 20:53:38 by dpotvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Just copy the 2D Array
void	ft_copy2darray(char ***dist, char **src)
{
	int		i;
	char	**new;

	new = malloc((ft_count2darray(src) + 1) * sizeof(char *));
	if (!new)
	{
		printf("Malloc error while making new Env\n");
		exit(1);
	}
	i = 0;
	while (src[i])
	{
		new[i] = ft_strdup(src[i]);
		if (!new[i])
		{
			printf("Malloc error while Copying Env\n");
			exit(1);
		}
		i++;
	}
	new[i] = 0;
	*dist = new;
}
