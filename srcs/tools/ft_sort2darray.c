/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort2darray.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotvin <dpotvin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:33:37 by dpotvin           #+#    #+#             */
/*   Updated: 2023/07/30 22:04:53 by dpotvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Bubble sort
void	ft_sort2darray(char ***strings)
{
	char	*temp;
	char	**strings_ptr;
	int		i;
	int		j;
	int		num_strings;

	num_strings = 0;
	strings_ptr = *strings;
	while (strings_ptr[num_strings])
		num_strings++;
	i = -1;
	while (++i < num_strings - 1)
	{
		j = -1;
		while (++j < num_strings - i - 1)
		{
			if (ft_strcmp(strings_ptr[j], strings_ptr[j + 1]) > 0)
			{
				temp = strings_ptr[j];
				strings_ptr[j] = strings_ptr[j + 1];
				strings_ptr[j + 1] = temp;
			}
		}
	}
}
