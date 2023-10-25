/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotvin <dpotvin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 19:09:08 by pbergero          #+#    #+#             */
/*   Updated: 2023/08/04 00:13:01 by dpotvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	perror_global(char *str)
{
	perror(str);
	g_last_result = EXIT_FAILURE;
}

// Update the OLDPWD and PWD in env
// Add_to_env automaticly overwrite the last value in ENV
static void	update_env_path(void)
{
	char	*oldpwd;
	char	buffer2[1000];
	char	buffer[1000];

	oldpwd = find_and_return("PWD=");
	if (oldpwd)
	{
		ft_bzero(buffer, 1000);
		ft_strlcat(buffer, "OLDPWD=", 8);
		ft_strlcat(buffer, oldpwd, ft_strlen(oldpwd) + 8);
		add_to_env(buffer);
		ft_bzero(buffer, 1000);
		getcwd(buffer2, 1000);
		ft_strlcat(buffer, "PWD=", 5);
		ft_strlcat(buffer, buffer2, ft_strlen(buffer2) + 5);
		add_to_env(buffer);
	}
	else
		perror_global("No [PWD=] ? ms_cd -> update_env_path()");
}

/*recreation of cd as a buitin for minishell*/
/*change current directory for the specified one in the input.arg*/
/*if input.arg == NULL redirect to root*/
void	ms_cd(char **args)
{
	char	*path;

	g_last_result = EXIT_SUCCESS;
	path = args[1];
	if (!args[1])
		path = "/";
	if (chdir(path) == -1)
	{
		perror_global("cd:");
		return ;
	}
	update_env_path();
}
