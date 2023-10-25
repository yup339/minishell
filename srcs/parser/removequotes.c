/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   removequotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotvin <dpotvin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:47:32 by dpotvin           #+#    #+#             */
/*   Updated: 2023/07/31 21:28:37 by dpotvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	theresanotherquote(char *str, char quote)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == quote)
			return (true);
	}
	return (false);
}

char	*remove_quotes(char *str)
{
	static char	newstr[2000];
	int			i;
	char		c;

	i = 0;
	ft_bzero(newstr, 2000);
	while (str[i])
	{
		if (ft_isquote(&str[i]))
		{
			c = str[i];
			if (theresanotherquote(&str[i + 1], c))
			{
				i++;
				while (str[i] != c)
					ft_charncat(newstr, str[i++], 1);
			}
			else
				ft_charncat(newstr, str[i], 1);
		}
		else
			ft_charncat(newstr, str[i], 1);
		i++;
	}
	return (newstr);
}
