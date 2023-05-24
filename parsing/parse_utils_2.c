/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 21:04:41 by loculy            #+#    #+#             */
/*   Updated: 2023/05/11 11:09:23 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_builtin	*parse_del_one(t_builtin *start)
{
	t_builtin		*start_del;
	t_raw_builtin	*raw;
	t_raw_builtin	*raw_del;

	if (!start)
		return (0);
	raw = start->raw;
	while (raw != 0)
		raw = raw->next;
	while (raw)
	{
		raw_del = raw;
		raw = raw->next;
		ftm_free(raw_del);
	}
	start_del = start;
	if (start != 0)
		start = start->next;
	ftm_free(start_del);
	return (start);
}

t_builtin	*parse_skip_one(t_builtin *start)
{
	t_builtin	*tmp;

	tmp = start;
	if (tmp != 0)
		tmp = tmp->next;
	return (tmp);
}

t_builtin	*parse_skip_space(t_builtin *start)
{
	t_builtin	*tmp;

	tmp = start;
	while (tmp != 0 && tmp->type == 0)
		tmp = parse_skip_one(tmp);
	return (tmp);
}
