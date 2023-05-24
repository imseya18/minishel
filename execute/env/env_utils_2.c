/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:52:33 by loculy            #+#    #+#             */
/*   Updated: 2023/05/11 11:06:45 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*env_get_user(t_env **env_lst)
{
	t_env	*temp;

	temp = *env_lst;
	while (temp)
	{
		if (ft_strcmp(temp->name, "USER") == 0)
			return (temp->content);
		temp = temp->next;
	}
	return ("user");
}

void	env_init(int i, char **argv, t_minishell *main)
{
	while (argv[i])
		ft_env_add_back(&main->var_env, ft_envnew(argv[i++]));
}

char	*ft_get_env(t_env **env_lst, char *name)
{
	t_env	*temp;

	temp = *env_lst;
	if (name == 0)
		return (0);
	if (ft_strcmp("?", name) == 0)
		return (ft_itoa(get_exit_code(1000)));
	while (temp)
	{
		if (ft_strcmp(temp->name, name) == 0)
			return (temp->content);
		temp = temp->next;
	}
	return (ft_strdup_(""));
}

void	ft_setrank(t_env **env)
{
	t_env	*current;

	current = *env;
	while (current)
	{
		current->rank = -1;
		current = current->next;
	}
}
