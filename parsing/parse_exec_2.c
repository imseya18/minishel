/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:21:30 by loculy            #+#    #+#             */
/*   Updated: 2023/05/24 15:52:39 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_builtin	*get_exec_flags_3(t_builtin *start, t_exec *exec, int *pose,
	t_command **all_cmd)
{
	char			*flag;
	t_builtin		*tmp;
	t_raw_builtin	*raw;

	tmp = parse_skip_space(start);
	flag = ft_strjoin_char(0, '-');
	while (tmp != 0 && tmp->type != 0)
	{
		if (tmp->type == -1)
			return (tmp);
		raw = tmp->raw;
		while (raw != 0)
		{
			flag = ft_strjoin_char(flag, raw->chara);
			raw = raw->next;
		}
		if (tmp != 0)
			tmp = tmp->next;
	}
	exec_add_flags(exec, flag);
	if (tmp != 0)
		tmp = tmp->next;
	return (get_exec_flags(tmp, exec, pose, all_cmd));
}

t_builtin	*get_exec_flags_2(t_builtin *start, t_exec *exec, int *pose,
	t_command **all_cmd)
{
	char			*flag;
	t_builtin		*tmp;
	t_raw_builtin	*raw;

	tmp = parse_skip_space(start);
	flag = 0;
	while (tmp != 0 && tmp->type != 0)
	{
		if (tmp->type == -1)
			return (tmp);
		raw = tmp->raw;
		while (raw != 0)
		{
			flag = ft_strjoin_char(flag, raw->chara);
			raw = raw->next;
		}
		if (tmp != 0)
			tmp = tmp->next;
	}
	exec_add_flags(exec, flag);
	if (tmp != 0)
		tmp = tmp->next;
	return (get_exec_flags(tmp, exec, pose, all_cmd));
}

t_builtin	*get_exec_flags(t_builtin *start, t_exec *exec, int *pose,
	t_command **all_cmd)
{
	t_builtin		*tmp;
	t_raw_builtin	*raw;

	*pose = 2;
	tmp = parse_skip_space(start);
	if (!tmp)
		return (tmp);
	if (tmp->type == -1)
		return (tmp);
	raw = tmp->raw;
	if (raw != 0 && raw->chara == '-')
	{
		if (raw->next != 0)
			return (get_exec_flags_2(tmp, exec, pose, all_cmd));
		else if (tmp->next != 0 && tmp->next->type != 0)
		{
			if (tmp != 0)
				tmp = tmp->next;
			return (get_exec_flags_3(tmp, exec, pose, all_cmd));
		}
	}
	return (tmp);
}

t_builtin	*get_exec_path(t_builtin *start, t_exec *exec, int *pose)
{
	t_builtin		*tmp;
	t_raw_builtin	*raw;

	*pose = 1;
	tmp = parse_skip_space(start);
	if (!tmp)
		return (tmp);
	while (tmp != 0 && tmp->type != 0)
	{
		if (tmp->type == -1)
			return (tmp);
		raw = tmp->raw;
		while (raw != 0)
		{
			exec->cmd_path = ft_strjoin_char(exec->cmd_path, raw->chara);
			raw = raw->next;
		}
		if (tmp != 0)
			tmp = tmp->next;
	}
	exec_add_flags(exec, ft_strdup_(exec->cmd_path));
	if (tmp != 0)
		tmp = tmp->next;
	return (tmp);
}

t_builtin	*get_exec_argum(t_builtin *start, t_exec *exec, t_command **all_cmd)
{
	t_builtin		*tmp;
	t_raw_builtin	*raw;
	char			*str;

	tmp = parse_skip_space(start);
	str = 0;
	(void)all_cmd;
	while (tmp != 0)
	{
		tmp = parse_skip_space(tmp);
		if (!tmp)
			return (tmp);
		raw = tmp->raw;
		if (tmp->type == -1)
			return (tmp);
		while (raw != 0)
		{
			if (!(tmp->next == 0 && tmp->type == 0))
				str = ft_strjoin_char(str, raw->chara);
			raw = raw->next;
		}
		tmp = tmp->next;
		str = get_exec_argum_str(tmp, str, exec);
	}
	return (tmp);
}
