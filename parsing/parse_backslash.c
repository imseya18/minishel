/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_backslash.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:17:10 by loculy            #+#    #+#             */
/*   Updated: 2023/05/01 15:24:57 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_backslash_noquote(t_builtin *btln)
{
	t_raw_builtin	*raw;
	t_raw_builtin	*back;

	back = 0;
	raw = btln->raw;
	while (raw != 0)
	{
		if (raw->chara == '\\')
		{
			if (back == 0)
				btln->raw = raw->next;
			else
				back->next = raw->next;
			back = raw;
			raw = raw->next;
			ftm_free(back);
		}
		back = raw;
		if (raw != 0)
			raw = raw->next;
	}
}

void	parse_backslash(t_builtin **head_bltn)
{
	t_builtin	*act_bltn;
	t_builtin	*back_bltn;

	act_bltn = *head_bltn;
	back_bltn = 0;
	while (act_bltn != 0)
	{
		if (act_bltn->type == 1)
		{
			parse_backslash_noquote(act_bltn);
			if (act_bltn->raw == 0)
			{
				if (back_bltn == 0)
					*head_bltn = act_bltn->next;
				else
					back_bltn->next = act_bltn->next;
				back_bltn = act_bltn;
				act_bltn = act_bltn->next;
				ftm_free(back_bltn);
			}
		}
		back_bltn = act_bltn;
		if (act_bltn != 0)
			act_bltn = act_bltn->next;
	}
}
