/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_echo_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:09:04 by loculy            #+#    #+#             */
/*   Updated: 2023/05/01 15:25:20 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_builtin	*get_echo_return_line_3(t_builtin *start, t_raw_builtin *raw,
	int *brkln)
{
	t_builtin	*tmp;

	tmp = start->next;
	while (tmp != 0 && tmp->type != 0 && tmp->raw != 0)
	{
		raw = tmp->raw;
		while (raw != 0)
		{
			if (raw->chara != 'n')
				return (start);
			raw = raw->next;
		}
		if ((tmp->next == 0 || tmp->next->type == 0 || tmp->next->raw == 0))
		{
			*brkln = 1;
			if (tmp->next == 0)
				return (tmp->next);
			tmp = tmp->next;
			return (get_echo_return_line(tmp->next, brkln));
		}
		tmp = parse_del_one(tmp);
	}
	return (start);
}

t_builtin	*get_echo_return_line_2(t_builtin *start, t_raw_builtin *raw,
	t_builtin *tmp, int *brkln)
{
	while (raw != 0)
	{
		if (raw->chara != 'n')
			return (start);
		raw = raw->next;
	}
	if ((tmp->next == 0 || tmp->next->type == 0 || tmp->next->raw == 0))
	{
		*brkln = 1;
		if (tmp->next == 0)
			return (tmp->next);
		tmp = tmp->next;
		return (get_echo_return_line(tmp->next, brkln));
	}
	return (start);
}

t_builtin	*get_echo_return_line(t_builtin *start, int *brkln)
{
	t_builtin		*tmp;
	t_raw_builtin	*raw;

	if (!start)
		return (start);
	raw = start->raw;
	tmp = start;
	if (raw != 0 && raw->chara == '-')
	{
		raw = raw->next;
		if (raw != 0)
			return (get_echo_return_line_2(start, raw, tmp, brkln));
		else
			return (get_echo_return_line_3(start, raw, brkln));
	}
	return (start);
}
