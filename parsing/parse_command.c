/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 02:23:47 by loculy            #+#    #+#             */
/*   Updated: 2023/05/16 15:24:13 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_cmd_list(t_builtin *start)
{
	t_builtin		*tmp;
	t_builtin		*tmp_del;
	t_raw_builtin	*raw;
	t_raw_builtin	*raw_del;

	if (!start)
		return ;
	tmp = start;
	while (tmp != 0)
	{
		raw = tmp->raw;
		while (raw != 0)
		{
			raw_del = raw;
			raw = raw->next;
			ftm_free(raw_del);
		}
		tmp_del = tmp;
		if (tmp != 0)
		{
			tmp = tmp->next;
			ftm_free(tmp_del);
		}
	}
}

void	parse_cmd_3(t_parsed_cmd **cmd, t_builtin **back,
	t_builtin **tmp)
{
	if ((*tmp) != 0 && (*tmp)->type == 10)
	{
		ft_cmndadd_back(cmd, ft_cmndnew((*tmp), 10));
		if ((*back) != 0)
			(*back)->next = 0;
		(*back) = (*tmp);
		if ((*tmp) != 0)
			(*tmp) = (*tmp)->next;
		(*back)->next = 0;
	}
	else
	{
		(*back) = (*tmp);
		if ((*tmp) != 0)
			(*tmp) = (*tmp)->next;
	}
}

void	parse_cmd_2(t_parsed_cmd **cmd, t_builtin **back,
	t_builtin **tmp)
{
	t_builtin	*start;

	start = *tmp;
	if ((*tmp) != 0 && (*tmp)->type != 10)
	{
		while ((*tmp) != 0 && (*tmp)->type != 10)
		{
			(*back) = (*tmp);
			(*tmp) = (*tmp)->next;
		}
		ft_cmndadd_back(cmd, ft_cmndnew(start, 1));
	}
	parse_cmd_3(cmd, back, tmp);
}

void	parse_cmd(t_builtin **head_bltn, t_parsed_cmd **cmd)
{
	t_builtin	*back;
	t_builtin	*tmp;

	tmp = *head_bltn;
	if (tmp == 0)
		return ;
	back = 0;
	while (tmp != 0)
		parse_cmd_2(cmd, &back, &tmp);
}
