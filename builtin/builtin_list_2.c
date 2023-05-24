/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_list_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:46:41 by loculy            #+#    #+#             */
/*   Updated: 2023/05/01 15:24:22 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cmndadd_back(t_parsed_cmd **lst, t_parsed_cmd *new)
{
	t_parsed_cmd	*act;

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

t_parsed_cmd	*ft_cmndnew(t_builtin *raw, int type)
{
	t_parsed_cmd			*blt;

	blt = ftm_malloc(sizeof(t_parsed_cmd));
	if (!blt)
		return (0);
	blt->type = type;
	blt->cmd = raw;
	blt->next = NULL;
	return (blt);
}
