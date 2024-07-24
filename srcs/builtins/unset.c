/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:12:10 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/24 17:56:07 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_unset(char **args, t_env **mini_env, t_env **new_export)
{
	int i;
	int j;
	char *string;
	
	i = 0;
	while (args[i] != NULL)
		i++;
	if (i == 1)
		return ;
	i = 0;
	while (args[i] != NULL)
	{
		j = 0;
		while (args[i][j] != '=' && args[i][j] != '\0')
			j++;
		if (ft_isprint(args[i][0]) && !ft_isalpha(args[i][0]))
				printf("minishell: %s: '%s': not a valid identifier\n",
					args[0], args[i]);
		node_remove(mini_env, args[i], j);
		string = ft_strjoin("declare -x ", args[i]);
		node_remove(new_export, string, j + 11);
		free(string);	
		i++;
	}
}