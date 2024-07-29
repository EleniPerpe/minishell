/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:09:57 by eperperi          #+#    #+#             */
/*   Updated: 2024/07/29 20:25:35 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
char    *create_final_env(char *env_line);
char    *find_expander(char *expander, t_env **mini_env);
char    *final_string(char *expander, char *line, int i, int j);
char    *create_null_expander(char *line);
char    *expander_fill(char *line, int i, t_env **mini_env)
{
    char    *expander;
    int     j;
    char    *env_line;
    char    *final;
    char    *env_value;
    j = 0;
    i++;
    while ((line[i + j] != ' ' && line[i + j] != '\'' && line[i + j] != '"')
        && line[i + j] != '\0' && line[i + j] != '$')
        j++;
    expander = (char *)ft_malloc(j + 1);
    ft_strlcpy(expander, &line[i], j + 1);
    expander[j] = '\0';
    if (i > 1)
    {
        if (line[i - 2] == '\'')
        {
            free(expander);
            return (line);
        }
    }
    env_line = find_expander(expander, mini_env);
    env_value = create_final_env(env_line);
    final = final_string(env_value, line, i, j);
    i = i + j;
    free(expander);
    return (final);
}
char    *final_string(char *expander, char *line, int i, int j)
{
    int     exp_len;
    int     line_len;
    char    *final;
    char    *before;
    char    *after;
    exp_len = ft_strlen(expander);
    line_len = ft_strlen(line) - j;
    final = (char *)ft_malloc(exp_len + line_len + 1);
    before = (char *)ft_malloc(i);
    ft_strlcpy(before, line, i);
    before[i - 1] = '\0';
    after = ft_strdup(line + i + j);
    if (!after)
    {
        free(final);
        free(before);
        return (NULL);
    }
    final[0] = '\0';
    ft_strlcat(final, before, exp_len + line_len + 1);
    ft_strlcat(final, expander, exp_len + line_len + 1);
    ft_strlcat(final, after, exp_len + line_len + 1);
    return (free(before), free(after), final);
}
char    *create_final_env(char *env_line)
{
    int     i;
    char    *res;
    int     total_len;
    if (ft_strcmp(env_line, " ") == 0)
        return (" ");
    total_len = ft_strlen(env_line);
    i = 0;
    while (env_line[i] != '=')
        i++;
    i++;
    res = (char *)ft_malloc(total_len - i + 1);
    ft_strlcpy(res, &env_line[i], total_len - i + 1);
    res[total_len - i] = '\0';
    return (res);
}
char    *find_expander(char *expander, t_env **mini_env)
{
    size_t  len;
    t_env *temp;
    temp = *mini_env;
    len = strlen(expander);
    while (temp != NULL)
    {
        if (ft_strncmp(expander, temp->line, len) == 0 && temp->line[len] == '=')
        {
            return (temp->line);
        }
        temp = temp->next;
    }
    return (" ");
}
