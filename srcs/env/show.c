/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotvin <dpotvin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:46:39 by dpotvin           #+#    #+#             */
/*   Updated: 2023/08/07 00:18:49 by dpotvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	show_env(void)
{
	int		i;
	char	**e;

	i = -1;
	e = *get_env();
	while (e[++i])
	{
		if (strncmp(e[i], "OLDPWD=", ft_strlen("OLDPWD=")))
			printf("%s\n", e[i]);
	}
}

void	show_env_export(void)
{
	int		i;
	int		j;
	char	**t;

	t = *get_env();
	i = -1;
	while (t[++i])
	{
		printf("declare -x ");
		if (!strcmp(t[i], "OLDPWD="))
		{
			printf("OLDPWD\n");
			continue ;
		}
		j = -1;
		while (t[i][++j])
		{
			printf("%c", t[i][j]);
			if (t[i][j] == '=')
				printf("\"");
		}
		printf("\"\n");
	}
	g_last_result = EXIT_SUCCESS;
}
