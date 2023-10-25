/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotvin <dpotvin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 04:34:14 by dpotvin           #+#    #+#             */
/*   Updated: 2023/08/08 06:41:20 by dpotvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Hold the HEREDOC file count
int	*get_heredoc_filecount(void)
{
	static int	count;

	return (&count);
}

// Hold the HEREDOC file name prefix
char	*get_heredoc_fileprefix(void)
{
	static char	prefix[30];
	static bool	init;

	if (!init)
	{
		ft_strlcat(prefix, "_hd_file_", ft_strlen("_hd_file_") + 1);
		init = true;
	}
	return (prefix);
}

// Get Unique filename
char	*get_uniquefilename(void)
{
	static char	temp[30];
	char		*value_itoa;
	int			len_filename;

	ft_bzero(temp, 30);
	value_itoa = ft_itoa(++(*get_heredoc_filecount()));
	len_filename = ft_strlen(get_heredoc_fileprefix());
	ft_strlcat(temp, get_heredoc_fileprefix(), len_filename + 1);
	ft_strlcat(temp, value_itoa, len_filename + ft_strlen(value_itoa) + 1);
	free(value_itoa);
	return (temp);
}

// Only used for Deleting the files
char	*get_currentfilename(void)
{
	static char	temp[30];
	char		*value_itoa;
	int			len_filename;

	ft_bzero(temp, 30);
	value_itoa = ft_itoa((*get_heredoc_filecount()));
	len_filename = ft_strlen(get_heredoc_fileprefix());
	ft_strlcat(temp, get_heredoc_fileprefix(), len_filename + 1);
	ft_strlcat(temp, value_itoa, len_filename + ft_strlen(value_itoa) + 1);
	free(value_itoa);
	return (temp);
}

void	delete_heredocs_files(void)
{
	int		count;
	char	*filename;

	count = *get_heredoc_filecount();
	while (count > 0)
	{
		filename = get_currentfilename();
		if (!access(filename, F_OK))
			unlink(filename);
		count = --(*get_heredoc_filecount());
	}
}
