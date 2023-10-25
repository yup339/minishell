/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findandremove.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotvin <dpotvin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:46:34 by dpotvin           #+#    #+#             */
/*   Updated: 2023/08/04 05:12:45 by dpotvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Backend for find_and_remove
static void	remove_from_env(char *str)
{
	char	**e;
	char	**newenv;

	e = *get_env();
	ft_remove2darray(&newenv, e, str);
	ft_sort2darray(&newenv);
	free_env();
	*get_env() = newenv;
}

// Find and Remove variable in Env
// pass hello=DIJASID and hello= var will be deleted
void	find_and_remove(char *str)
{
	int		i;
	char	varname[200];

	i = -1;
	ft_bzero(varname, 200);
	while (str[++i])
	{
		if (str[i] == '=')
		{
			ft_strncat(varname, str, i + 1);
			remove_from_env(varname);
			return ;
		}
	}
}

// Find and Return variable in Env
// pass ARG= , and its value will be returned
char	*find_and_return(char *str)
{
	int		i;
	int		len;
	char	**e;

	i = -1;
	e = *get_env();
	len = ft_strlen(str);
	while (e[++i])
	{
		if (!ft_strncmp(e[i], str, len))
			return (&e[i][len]);
	}
	return ("");
}

void	rem_from_env(char *argname)
{
	char	name[200];
	char	**e;

	e = *get_env();
	ft_bzero(name, 200);
	ft_strncat(name, argname, ft_strlen(argname));
	ft_charncat(name, '=', 1);
	find_and_remove(name);
	g_last_result = EXIT_SUCCESS;
}
