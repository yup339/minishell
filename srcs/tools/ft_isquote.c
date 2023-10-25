/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isquote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotvin <dpotvin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:33:22 by dpotvin           #+#    #+#             */
/*   Updated: 2023/07/30 20:33:23 by dpotvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Return a non-zero value if its a quote, return its uint8_t value
// so we can also store what kind is it
uint8_t	ft_isquote(char	*str)
{
	if (!ft_strncmp(str, "\"", 1))
		return (1);
	else if (!ft_strncmp(str, "'", 1))
		return (2);
	return (0);
}
