/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotvin <dpotvin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:25:08 by pbergero          #+#    #+#             */
/*   Updated: 2023/08/08 05:31:35 by dpotvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	convert_exit(void)
{
	if (WIFEXITED(g_last_result))
	{
		g_last_result = WEXITSTATUS(g_last_result);
	}
	else if (WIFSIGNALED(g_last_result))
	{
		g_last_result = WTERMSIG(g_last_result) + 128;
	}
}

/*free what needs to be freed in here when an error occors*/
//	unlink_path(NULL);
// yavais ca entre get_env & temp_env, commented
void	clean_static_memory(void)
{
	rl_clear_history();
	free_env();
	save_std(CLOSE_IN | CLOSE_OUT);
}

static void	exit_process_argument(char *arg)
{
	if (is_valid_longlong(arg))
	{
		g_last_result = ft_longlongatoi(arg);
	}
	else
	{
		ft_putstr_fd("Minishell: exit: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": numeric argument required", 2);
		g_last_result = 255;
	}
}

/*recreation of exit as a buitin for minishell*/
/*closes the minishell program and free current input used to call it*/
void	ms_exit(t_input *input)
{
	if (!input || get_array_size(input->commands) == 1)
	{
		clean_static_memory();
		delete_heredocs_files();
		free_input(input);
		exit(g_last_result);
	}
	if (get_array_size(input->commands) > 2)
	{
		ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
		g_last_result = EXIT_FAILURE;
		return ;
	}
	exit_process_argument(input->commands[1]);
	clean_static_memory();
	delete_heredocs_files();
	free_input(input);
	exit(g_last_result);
}
