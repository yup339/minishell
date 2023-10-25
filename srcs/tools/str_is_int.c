/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_is_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotvin <dpotvin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 20:59:02 by pbergero          #+#    #+#             */
/*   Updated: 2023/08/04 06:50:18 by dpotvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	is_valid_longlong(const char *str)
{
	int			i;
	int			sign;
	long long	nbr;

	if (!str)
		return (false);
	i = 0;
	nbr = 0;
	sign = 1;
	if (!ft_strcmp(str, "-9223372036854775808"))
		return (true);
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (nbr > (LLONG_MAX - (str[i] - '0')) / 10)
			return (false);
		nbr = (nbr * 10) + (str[i++] - '0');
	}
	return (str[i] == 0);
}

int	is_str_int2(const char *str, int len)
{
	if (len > 11)
		return (0);
	if (len == 11)
	{
		if (str[0] != '-')
			return (0);
		if (str[0] == '-' && ft_strcmp(str, "-2147483648") > 0)
			return (0);
	}
	if (len == 10)
	{
		if (ft_strcmp(str, "2147483647") > 0)
			return (0);
	}
	return (1);
}

int	is_str_int(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[0] == '-')
		i++;
	if (str[i] == '\0')
		return (0);
	while ((str[i]))
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (is_str_int2(str, ft_strlen(str)));
}
