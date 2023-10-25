/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbergero <pascaloubergeron@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 05:56:50 by dpotvin           #+#    #+#             */
/*   Updated: 2023/08/04 23:17:44 by pbergero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Remove variable from env
// We start at index 1 since the 0 is the command AKA unset
void	ms_unset(char **args)
{
	int	i;

	i = 1;
	while (args[i])
		rem_from_env(args[i++]);
}
