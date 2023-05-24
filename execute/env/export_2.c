/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:46:30 by mmorue            #+#    #+#             */
/*   Updated: 2023/05/22 16:38:54 by mmorue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_lstsize_env(t_env *lst)
{
	t_env	*act;
	int		size;

	if (!lst)
		return (0);
	size = 1;
	act = lst;
	while (act->next != NULL)
	{
		size++;
		act = act->next;
	}
	return (size);
}

char	*ft_printenv_export_disp(t_env *current, char *env)
{
	if (!current->content)
		env = infinit_join("4", env, "declare -x ", current->name, "\n");
	else
	{
		env = infinit_join("6", env, "declare -x ", current->name, "=\"",
				current->content, "\"\n");
	}
	return (env);
}

char	*ft_printenv_export(t_env **env)
{
	t_env	*current;
	t_env	*next;
	int		i;
	int		size_lst;
	char	*tab_env;

	tab_env = ft_strdup_("");
	size_lst = ft_lstsize_env(*env);
	i = 0;
	ft_setrank(env);
	current = *env;
	next = current->next;
	ft_assignrank(i, size_lst, current, next);
	while (i < size_lst)
	{	
		current = *env;
		while (current)
		{
			if (current->rank == i)
				tab_env = ft_printenv_export_disp(current, tab_env);
			current = current->next;
		}
		i++;
	}
	return (tab_env);
}

void	ft_assignrank(int i, int size_lst, t_env *current, t_env *next)
{
	t_env	*temp;

	temp = current;
	while (i < size_lst)
	{
		while (current->rank != -1 && current)
			current = current->next;
		next = current->next;
		current->rank = i;
		while (next)
		{
			if (next->rank == -1)
			{
				if (ft_strcmp(current->name, next->name) > 0)
				{
					next->rank = i;
					current->rank = -1;
					current = next;
				}
			}
			next = next->next;
		}
		i++;
		current = temp;
	}
}
