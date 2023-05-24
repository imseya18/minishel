/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorue <mmorue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:39:10 by loculy            #+#    #+#             */
/*   Updated: 2023/05/24 15:28:54 by mmorue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*ft_envnew(char *str)
{
	t_env			*env_link;

	env_link = ftm_malloc(sizeof(t_env));
	if (!env_link)
		return (0);
	env_link->name = ft_get_env_name(str);
	env_link->content = ft_get_env_content(str);
	env_link->next = NULL;
	return (env_link);
}

void	ft_env_add_back(t_env **lst, t_env *new)
{
	t_env	*act;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	act = *lst;
	while (act->next != NULL)
		act = act->next;
	act->next = new;
}

char	*ft_get_env_name(char *str)
{
	int		i;
	char	*name;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	name = ftm_malloc((i + 1) * sizeof(char));
	name[i] = '\0';
	i = 0;
	while (str[i] != '=' && str[i] != '\0')
	{
		name[i] = str[i];
		i++;
	}
	return (name);
}

char	*ft_get_env_content(char *str)
{
	int		i;
	int		k;
	int		temp;
	char	*content;

	i = 0;
	k = 0;
	while (str[i] != '=' && str[i])
		i++;
	temp = ++i;
	while (str[i++])
		k++;
	content = ftm_malloc((k + 1) * sizeof(char));
	content[k] = '\0';
	k = 0;
	while (str[temp])
		content[k++] = str[temp++];
	return (content);
}

char	*ft_printenv(t_env *env)
{
	char	*tab_env;
	char	*temp;

	tab_env = ft_strdup_("");
	while (env)
	{
		if (env->content != 0)
		{
			temp = tab_env;
			tab_env = infinit_join("5", tab_env, env->name, "=",
					env->content, "\n");
			ftm_free(temp);
		}
		env = env->next;
	}
	get_exit_code(0);
	return (tab_env);
}
