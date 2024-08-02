/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:27:07 by rshatra           #+#    #+#             */
/*   Updated: 2024/08/02 19:34:35 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	start_prompt(t_env **mini_env, t_env **new_export, int i)
{
	char		*whole_line;
	t_input		*new_input_node;
	int			processes_num;
	int			**pro_pid;
	int			**pipe_fd;
	int exit2;

	new_input_node = NULL;
	while (1)
	{
		i = 0;
		reset_io(); // need to modify it to take STD IN and OUT from before the while
		whole_line = readline("minishell >");
		if (!whole_line) // EOF : ctrl+D
		{
			printf("exit\n");
			exit (EXIT_FAILURE) ;
		}
		add_history(whole_line);
		processes_num =  split_pipes(whole_line, &new_input_node);
		if (init_linked_list(&new_input_node, mini_env) == 0)
		{
			// init_linked_list(&new_input_node, mini_env);
			pipe_fd =  pipes_init(processes_num);
			pro_pid  = pid_init(processes_num);
			exit2 = check_for_builtins(new_input_node->cmd_args, mini_env, new_export);
			if (processes_num == 1 && exit2 != -2)
			{
				change_status(mini_env, exit2);
				new_input_node = NULL;
				// new_input_node = new_input_node->next;
			}
			else
			{
				while (i < processes_num)
				{
					if (fork_and_exec(new_input_node, pro_pid[i], pipe_fd, mini_env, new_export) != 0)
					{
						exit(EXIT_FAILURE);
					}
						/*change_status(mini_env, 0)*/ ;
					new_input_node = new_input_node->next;
					i++;
				}
				close_fds(pipe_fd);
				wait_for_children(pro_pid, processes_num, mini_env);
				free_all(&new_input_node, pro_pid, pipe_fd); // not done, need a lot of work
			}
		}
		else
			new_input_node = new_input_node->next;
	}
}


int	process_execution(t_input *data, int **pipe_fd , t_env **mini_env, t_env **new_export)
{
	int processes_num;
	t_input *tmp;
	int		builtin;

	tmp = data;
	while (tmp->next)
		tmp = tmp->next;
	processes_num = tmp->i + 1;
	if (standard_io(data, pipe_fd, data->i, processes_num, mini_env) != 0)
		return (1);
	close_fds(pipe_fd);
	builtin = check_for_builtins(data->cmd_args, mini_env, new_export);
	if (builtin != -2)
	{
		// data = NULL;
		change_status(mini_env, builtin);
		exit (builtin);
	}
	else if (builtin == -2)
	{
		if (exec_command(data->cmd_args, mini_env) != 0)
			return (1);
	}
	return(0);
}

int	fork_and_exec(t_input *data, int *process_pid, int **pipe_fd, t_env **mini_env, t_env **new_export)
{

	t_input *new_input_node;
	int		*cur_pro_pid;

	cur_pro_pid = process_pid;
	new_input_node = data;
	setup_signal_exe();
	if (!ft_strncmp(data->cmd_args[0], "exit", 4))
	{
		modify_shlvl(mini_env, '-');
		ft_exit(data->cmd_args, mini_env);
	}
	cur_pro_pid[0] = fork();
	if (cur_pro_pid[0] < 0)
	{
		// eroor_handle
		exit(EXIT_FAILURE);
	}
	else if (cur_pro_pid[0]== 0)
	{
		if (process_execution(new_input_node, pipe_fd, mini_env, new_export) != 0)
			return (1);
			// exit(EXIT_SUCCESS); // not necessary
	}
	return (0);
}
