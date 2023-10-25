/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isvariable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotvin <dpotvin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:33:29 by dpotvin           #+#    #+#             */
/*   Updated: 2023/07/31 00:23:28 by dpotvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*get_arg_name(char *str, char delim)
{
	int			i;
	int			j;
	static char	temp[100];

	i = 0;
	j = 0;
	ft_bzero(temp, 100);
	while (str[i] && str[i] != delim)
		temp[j++] = str[i++]; 
	temp[j] = '=';
	return (find_and_return(temp));
}

static bool	isvalidchar(char c)
{
	return (ft_isalpha(c) || ft_isdigit(c) || c == '_');
}

static char	*get_arg_name2(char *str)
{
	int			i;
	int			j;
	static char	temp[100];

	i = 0;
	j = 0;
	ft_bzero(temp, 100);
	temp[j++] = str[i++];
	while (str[i] && isvalidchar(str[i]))
		temp[j++] = str[i++]; 
	temp[j] = '=';
	return (find_and_return(temp));
}

char	*ft_isvariable(char *str)
{
	int			i;
	char		*temp;
	static char	cashreturn[11];

	i = 0;
	if (str[i] == '$')
	{
		i++;
		if (str[i] == '{')
			return (get_arg_name(&str[++i], '}'));
		else if (str[i] == '?')
		{
			ft_bzero(cashreturn, 11);
			temp = ft_itoa(g_last_result);
			ft_strcpy(cashreturn, temp);
			free(temp);
			return (cashreturn);
		}
		else if (ft_isalpha(str[i]) || str[i] == '_')
			return (get_arg_name2(&str[i]));
	}
	return (0);
}
