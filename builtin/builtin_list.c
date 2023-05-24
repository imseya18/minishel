/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:46:41 by loculy            #+#    #+#             */
/*   Updated: 2023/05/01 15:24:19 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_bltnadd_back(t_builtin **lst, t_builtin *new)
{
	t_builtin	*act;

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

t_builtin	*ft_bltnnew(t_raw_builtin *raw, int type)
{
	t_builtin			*blt;

	blt = ftm_malloc(sizeof(t_builtin));
	if (!blt)
		return (0);
	blt->type = type;
	blt->raw = raw;
	blt->next = NULL;
	return (blt);
}

void	ft_rawadd_back(t_raw_builtin **lst, t_raw_builtin *new)
{
	t_raw_builtin	*act;

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

t_raw_builtin	*ft_rawnnew(char chara)
{
	t_raw_builtin			*blt;

	blt = ftm_malloc(sizeof(t_raw_builtin));
	if (!blt)
		return (0);
	blt->chara = chara;
	blt->next = NULL;
	return (blt);
}
