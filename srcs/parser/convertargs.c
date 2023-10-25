/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convertargs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotvin <dpotvin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:47:28 by dpotvin           #+#    #+#             */
/*   Updated: 2023/08/08 05:09:44 by dpotvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*convert_all_args(char *command)
{
	char		*var;
	int			data[3];
	static char	newstr[2000];

	ft_bzero(data, sizeof(data));
	ft_bzero(newstr, 2000);
	while (command[data[0]])
	{
		if (ft_isquote(&command[data[0]]) && !data[2])
			data[2] = command[data[0]];
		else if (ft_isquote(&command[data[0]]) && data[2] == command[data[0]])
			data[2] = 0;
		if (data[2] != 39 && ft_isvariable(&command[data[0]]))
		{
			data[1] = ft_getvariablelen(&command[data[0]]);
			var = ft_isvariable(&command[data[0]]);
			ft_strncat(newstr, var, data[0] + ft_strlen(var) + 2);
			data[0] += data[1];
		}
		else
			ft_charncat(newstr, command[data[0]++], 1);
	}
	return (newstr);
}

char	*convert_all_args_hd(char *command)
{
	char		*var;
	int			data[3];
	static char	newstr[2000];

	ft_bzero(data, sizeof(data));
	ft_bzero(newstr, 2000);
	while (command[data[0]])
	{
		if (ft_isvariable(&command[data[0]]))
		{
			data[1] = ft_getvariablelen(&command[data[0]]);
			var = ft_isvariable(&command[data[0]]);
			ft_strncat(newstr, var, data[0] + ft_strlen(var) + 2);
			data[0] += data[1];
		}
		else
			ft_charncat(newstr, command[data[0]++], 1);
	}
	return (newstr);
}
