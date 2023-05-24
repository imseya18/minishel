/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:50:05 by loculy            #+#    #+#             */
/*   Updated: 2023/05/23 23:02:31 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_free_unset(t_env *temp)
{
	ftm_free(temp->name);
	ftm_free(temp->content);
	ftm_free(temp);
}

char	*error_unset(t_unset *unset)
{
	ft_printerror("minishell: export: %s\n", unset->error_msg);
	set_exit_code(1);
	return (ft_strdup_(""));
}

char	*ft_unset(t_env **env_lst, t_unset *unset)
{
	t_env	*temp;
	t_env	*back;

	if (unset->error_msg != 0)
		return (error_unset(unset));
	if (env_lst == NULL)
		return (ft_strdup_(""));
	temp = *env_lst;
	back = NULL;
	while (temp)
	{
		if (ft_strcmp(temp->name, unset->name) == 0)
		{
			if (back)
				back->next = temp->next;
			else
				*env_lst = temp->next;
			ft_free_unset(temp);
			return (ft_strdup_(""));
		}
		back = temp;
		temp = temp->next;
	}
	set_exit_code(0);
	return (ft_strdup_(""));
}
