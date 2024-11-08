/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:49:34 by eperperi          #+#    #+#             */
/*   Updated: 2024/08/08 17:53:13 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dup_inout(t_inout *inout_main)
{
	inout_main->input = dup(STDIN_FILENO);
	inout_main->output = dup(STDOUT_FILENO);
}

int	main(int argc, char **argv, char **env)
{
	t_env	*mini_env;
	t_env	*new_export;
	t_inout	main_inout;

	mini_env = NULL;
	new_export = NULL;
	setup_signal_init();
	dup_inout(&main_inout);
	create_path(env, &mini_env);
	modify_shlvl(&mini_env, '+');
	create_export_path(&mini_env, &new_export);
	(void)argv;
	if (argc != 1)
	{
		printf("This program doesn't take any arguments!\n");
		return (1);
	}
	start_prompt(&mini_env, &new_export, main_inout);
	return (0);
}
