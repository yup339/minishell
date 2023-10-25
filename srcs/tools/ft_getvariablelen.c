/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getvariablelen.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotvin <dpotvin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:33:09 by dpotvin           #+#    #+#             */
/*   Updated: 2023/07/30 21:38:56 by dpotvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	isvalidchar(char c)
{
	return (ft_isalpha(c) || ft_isdigit(c) || c == '_');
}

static void	double_increment(int *i, int *len)
{
	(*i)++;
	(*len)++;
}

int	ft_getvariablelen(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (str[i] == '$')
	{
		i++;
		if (str[i] == '{')
		{
			while (str[i] && str[i] != '}')
				double_increment(&i, &len);
			return (len + 2);
		}
		else if (str[i] == '?')
			return (2);
		else if (ft_isalpha(str[i]) || str[i] == '_')
		{
			double_increment(&i, &len);
			while (str[i] && isvalidchar(str[i]))
				double_increment(&i, &len);
			return (len + 1);
		}
	}
	return (len);
}
