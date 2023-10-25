/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isin2darray.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotvin <dpotvin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:33:20 by dpotvin           #+#    #+#             */
/*   Updated: 2023/07/30 21:42:06 by dpotvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	ft_isin2darray(char **src, char *tofind)
{
	int				i;
	unsigned int	size;

	i = -1;
	size = ft_strlen(tofind);
	while (src[++i])
	{
		if (!ft_strncmp(src[i], tofind, size))
			return (true);
	}
	return (false);
}
