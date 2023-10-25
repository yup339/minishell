/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotvin <dpotvin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:33:57 by dpotvin           #+#    #+#             */
/*   Updated: 2023/07/31 21:37:59 by dpotvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_strtok_monkas(char *str)
{
	char	*commands;
	char	*temp;
	int		i;

	i = 0;
	temp = ft_strdup(str);
	commands = ft_strtok_monkas(temp);
	while (commands)
	{
		i++;
		commands = ft_strtok_monkas(NULL);
	}
	free(temp);
	return (i);
}

char	*ft_strtok(char *str)
{
	static char	*output;
	static char	*stock;
	uint8_t		data[2];

	ft_strtokhelper3(&output, &data[0], &data[1]);
	if (str)
		stock = str;
	while (*stock)
	{
		if (!data[1] && !(*stock == '|'))
		{
			data[1] = true;
			output = stock;
		}
		else if (data[1] && !data[0] && *stock == '|')
		{
			*stock = 0;
			stock++;
			break ;
		}
		ft_strtokhelper2(&data[1], &data[0], &stock);
	}
	return (output);
}

static char	*return_redirtype(char **stock)
{
	if (!ft_strncmp(*stock, "<<", 2))
	{
		(*stock) += 2;
		return ("<<");
	}
	else if (!ft_strncmp(*stock, ">>", 2))
	{
		(*stock) += 2;
		return (">>");
	}
	else if (!ft_strncmp(*stock, "<", 1))
	{
		(*stock)++;
		return ("<");
	}
	else
	{
		(*stock)++;
		return (">");
	}
}

void	strtok_helper(char *str, char **stock, char *last_char)
{
	if (str)
		*stock = str;
	if (*last_char != '\0')
	{
		**stock = *last_char;
		*last_char = '\0';
	}
	while (**stock != '\0' && isspace(**stock))
		(*stock)++;
}

// cancer ahead
char	*ft_strtok_monkas(char *str)
{
	static char	*output;
	static char	*stock;
	uint8_t		data[2];
	static char	last_char;

	ft_strtokhelper3(&output, &data[0], &data[1]);
	strtok_helper(str, &stock, &last_char);
	if (ft_isredir(stock))
		return (return_redirtype(&stock));
	while (*stock)
	{
		if (!data[1] && !(ft_isspace(*stock)))
			strtok_one(&data[1], &output, stock);
		else if (data[1] && !data[0] && ft_isspace(*stock))
		{
			strtok_two(&stock);
			break ;
		}
		if (data[1] && !data[0] && ft_isredir(stock)
			&& stok3(&stock, &last_char))
			break ;
		ft_strtokhelper2(&data[1], &data[0], &stock);
	}
	return (output);
}
