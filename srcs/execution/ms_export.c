/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotvin <dpotvin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 03:39:10 by dpotvin           #+#    #+#             */
/*   Updated: 2023/08/04 05:13:30 by dpotvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Add the variable to Env
void	ms_export(char **args)
{
	int	i;

	i = 1;
	if (!args[1])
		show_env_export();
	while (args[i])
		add_to_env(args[i++]);
}
