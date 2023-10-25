/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove2darray.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotvin <dpotvin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:33:35 by dpotvin           #+#    #+#             */
/*   Updated: 2023/07/31 21:20:10 by dpotvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Copy 2d Array and remove Str
void	ft_remove2darray(char ***dist, char **src, char *str)
{
	int		i;
	int		j;
	char	**new;

	new = malloc((ft_count2darray(src) + 1) * sizeof(char *));
	if (!new)
	{
		printf("Malloc error while making new Env\n");
		exit(1);
	}
	i = -1;
	j = -1;
	while (src[++i])
	{
		if (!ft_strncmp(src[i], str, ft_strlen(str)))
			continue ;
		new[++j] = ft_strdup(src[i]);
		if (!new[j])
		{
			printf("Malloc error while Copying Env\n");
			exit(1);
		}
	}
	new[++j] = 0;
	*dist = new;
}
