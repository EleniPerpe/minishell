/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleni <eleni@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:00:29 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/03 18:24:39 by eleni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void add_path_to_list(t_env **mini_env, t_env *new_env);

void create_path(char **env, t_env **mini_env)
{
	t_env *new_env;
	t_env *tmp;
	int i;
	int j;

	i = 0;
	while (env[i] != NULL)
	{
		printf("Env : %s\n", env[i]);
		i++;
	}
	i = 0;
	while (env[i] != NULL)
	{
		new_env = (t_env *)ft_malloc(sizeof(t_env));
		j = ft_strlen(env[i]);
		new_env->line = (char *)ft_malloc(j + 1);
		ft_strlcpy(new_env->line, env[i], j);
		new_env->line[j] = '\0';
		new_env->next = NULL;
		add_path_to_list(mini_env, new_env);
		i++;
	}

	tmp = *mini_env; // prints the path
	while (tmp != NULL)
	{
		printf("Next line : %s\n", tmp->line);
		tmp = tmp->next;
	}
	
	// for later
	
	// while (new_env != NULL)
	// {
	// 	tmp = new_env;
	// 	new_env = new_env->next;
	// 	free(tmp);
	// }
}

void add_path_to_list(t_env **mini_env, t_env *new_env)
{
	t_env *tmp;

	if (*mini_env == NULL)
		*mini_env = new_env;
	else
	{
		tmp = *mini_env;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_env;
	}
}

char *expander_fill(char *line, int *i, t_line_data **data)
{
	t_line_data *new_line_data;
	char *expander;
	int j;

	printf("hiiiii\n");

	new_line_data = (t_line_data *)ft_malloc(sizeof(t_line_data));
	j = 0;
	(*i)++;
	while (line[*i + j] != ' ' && line[*i + j] != '\0')
		j++;
	printf("i : %d and j : %d\n", *i, j);
	expander = (char *)ft_malloc(j + 1);
	ft_strlcpy(expander, &line[*i], j + 1);
	expander[j] = '\0';
	*i = *i + j;
	// printf("expander : %s and i : %d\n", expander, *i);
	new_line_data->type = 1;
	new_line_data->command = NULL;
	new_line_data->redirctor = NULL;
	new_line_data->after_redirctor = NULL;
	new_line_data->next = NULL;
	new_line_data->expander = (char *)ft_malloc(j + 1);
	new_line_data->expander = expander;
	new_line_data->expander[j] = '\0';
	printf("Expander is : %s", new_line_data->expander);
	add_node_to_list(data, new_line_data);
	return (expander);
	// return (char *);
}