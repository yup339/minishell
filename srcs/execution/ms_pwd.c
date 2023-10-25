/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbergero <pascaloubergeron@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 21:48:47 by pbergero          #+#    #+#             */
/*   Updated: 2023/08/09 15:49:05 by pbergero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*recreation of exit as a buitin for minishell*/
/*print the current working directory */
void	ms_pwd(char **args)
{
	char		pwd[1024];
	static char	delpwd[1024];

	g_last_result = 0;
	(void)args;
	if (getcwd(pwd, sizeof(pwd)))
	{
		ft_memcpy(delpwd, pwd, sizeof(pwd));
		printf("%s\n", pwd);
	}
	else
	{
		printf("%s\n", delpwd);
	}
}

static void	check_permission_rights(char *path)
{
	if (!ft_strncmp("./", path, 2))
	{
		access(path, X_OK);
		if (errno == EACCES)
			g_last_result = PERMISSION_DENIED_EXIT;
	}
}

int	get_file_type(char *path)
{
	struct stat	path_stat;

	if (!stat(path, &path_stat))
	{
		if (S_ISREG(path_stat.st_mode)
			&& !(path_stat.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)))
		{
			g_last_result = COMMAND_NOT_FOUND_EXIT;
			check_permission_rights(path);
			return (NORMAL_FILE);
		}
		else if (S_ISDIR(path_stat.st_mode) && (!ft_strncmp(path, "./", 2)
				|| !ft_strncmp(path, "/", 1)))
		{
			errno = EISDIR;
			g_last_result = IS_DIR_EXIT;
			return (DIR);
		}
		else
			return (EXE);
	}
	g_last_result = COMMAND_NOT_FOUND_EXIT;
	check_permission_rights(path);
	return (NORMAL_FILE);
}

void	error_message_exe(char *str)
{
	get_file_type(str);
	if (errno == ENOENT && ft_strncmp(str, "./", 2))
	{
		ft_putstr_fd("Minishell: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	}
	else
		perror(str);
}

void	dup_last_fd(t_fd_chain *fd_chain)
{
	while (fd_chain->next)
	{
		close(fd_chain->fd[1]);
		close(fd_chain->fd[0]);
		fd_chain = fd_chain->next;
	}
	close(fd_chain->fd[1]);
	dup2(fd_chain->fd[0], STDIN_FILENO);
	close(fd_chain->fd[0]);
}
