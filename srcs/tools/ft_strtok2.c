/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotvin <dpotvin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 00:33:31 by dpotvin           #+#    #+#             */
/*   Updated: 2023/07/31 21:38:21 by dpotvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_strtokhelper2(uint8_t *swtch, uint8_t *quote, char **stock)
{
	if (*swtch && !*quote && ft_isquote(*stock))
		*quote = ft_isquote(*stock);
	else if (*swtch && *quote && *quote == ft_isquote(*stock))
		*quote = 0;
	(*stock)++;
}

void	ft_strtokhelper3(char **output, uint8_t *quote, uint8_t *swtch)
{
	*output = 0;
	*quote = 0;
	*swtch = 0;
}

void	strtok_one(uint8_t *swtch, char **output, char *stock)
{
	*swtch = 1;
	*output = stock;
}

void	strtok_two(char **stock)
{
	**stock = 0;
	(*stock)++;
}

bool	stok3(char **stock, char *last_char)
{
	*last_char = **stock;
	**stock = 0;
	return (true);
}
