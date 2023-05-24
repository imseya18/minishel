/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_in_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:32:26 by loculy            #+#    #+#             */
/*   Updated: 2023/05/19 13:20:24 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirect_c_two_things(t_command **all_cmd, t_redirection *redi)
{
	ft_cmd_add_back(all_cmd, ft_cmdnew(redi, redi->type));
	set_stdin(redi->value, redi, redi->value_type);
}

t_builtin	*get_redirection_in_file_a(t_builtin *start, t_command **all_cmd,
	t_redirection *redi)
{
	t_builtin		*tmp;
	t_raw_builtin	*raw;

	tmp = start;
	if (!tmp)
		return (tmp);
	tmp = parse_skip_space(tmp->next);
	while (tmp != 0 && tmp->type != 0)
	{
		raw = tmp->raw;
		while (raw != 0)
		{
			redi->file_name = ft_strjoin_char(redi->file_name, raw->chara);
			raw = raw->next;
		}
		tmp = tmp->next;
	}
	ft_cmd_add_back(all_cmd, ft_cmdnew(redi, redi->type));
	set_stdin(redi->value, redi, redi->value_type);
	if (tmp != 0)
		tmp = tmp->next;
	return (parse_skip_space(tmp));
}

t_builtin	*get_redirection_in_file_b(t_builtin *start, t_command **all_cmd,
	t_redirection *redi, int skip)
{
	t_builtin		*tmp;
	t_raw_builtin	*raw;
	int				index;

	tmp = start;
	index = 0;
	redirect_c_two_things(all_cmd, redi);
	if (!tmp)
		return (tmp);
	while (tmp != 0 && tmp->type != 0)
	{
		raw = tmp->raw;
		if (index == 0 && skip == 1)
			raw = raw->next;
		while (raw != 0)
		{
			redi->file_name = ft_strjoin_char(redi->file_name, raw->chara);
			raw = raw->next;
			index++;
		}
		tmp = tmp->next;
	}
	if (tmp != 0)
		tmp = tmp->next;
	return (parse_skip_space(tmp));
}

t_builtin	*get_redirection_in(t_builtin *start, int type, void *main_cmd,
	t_command **all_cmd)
{
	t_builtin		*tmp;
	t_raw_builtin	*raw;
	t_redirection	*redi;

	tmp = start;
	if (tmp != 0 && tmp->type == 1 && tmp->raw != 0 && tmp->raw->chara == '<')
	{
		redi = add_redirection(type, 103, main_cmd);
		raw = tmp->raw->next;
		if (raw != 0)
		{
			if (raw->chara == '<')
				redi->type = 104;
			if (raw->chara == '<')
				raw = raw->next;
			if (raw != 0 && (raw->chara == '>' || raw->chara == '<'))
				return (get_redirection_err(type, raw, main_cmd, raw->chara));
			if (redi->type == 104)
				return (get_redirection_in_separator(tmp, all_cmd, redi));
			else
				return (get_redirection_in_file_b(tmp, all_cmd, redi, 1));
		}
		return (get_redirection_in_file_a(tmp, all_cmd, redi));
	}
	return (start);
}
