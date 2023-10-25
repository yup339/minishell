/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbergero <pascaloubergeron@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 12:43:10 by dpotvin           #+#    #+#             */
/*   Updated: 2023/08/02 22:49:48 by pbergero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	char	*str;

	str = malloc(nitems * size);
	if (!str)
		return (0);
	ft_bzero(str, nitems * size);
	return (str);
}
