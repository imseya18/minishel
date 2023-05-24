/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:15:50 by loculy            #+#    #+#             */
/*   Updated: 2023/05/05 12:33:26 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redirection	*add_redirection(int val_type, int type, void *main_cmd)
{
	t_redirection			*cmdrdct;

	cmdrdct = ftm_malloc(sizeof(t_redirection));
	if (!cmdrdct)
		return (0);
	cmdrdct->type = type;
	cmdrdct->file_name = 0;
	cmdrdct->value = main_cmd;
	cmdrdct->value_type = val_type;
	cmdrdct->error = 0;
	cmdrdct->error_msg = NULL;
	redi_printable(val_type, main_cmd);
	return (cmdrdct);
}

t_builtin	*get_redirection_2(t_builtin *tmp, t_command **all_cmd,
	t_raw_builtin *raw, t_redirection *redi)
{
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
	if (tmp != 0)
		tmp = tmp->next;
	return (parse_skip_space(tmp));
}

t_builtin	*get_redirection_3(t_builtin *tmp, t_command **all_cmd,
	t_raw_builtin *raw, t_redirection *redi)
{
	if (!raw)
		return (get_redirection_2(tmp, all_cmd, raw, redi));
	while (raw != 0)
	{
		redi->file_name = ft_strjoin_char(redi->file_name, raw->chara);
		raw = raw->next;
	}
	tmp = get_redirection_in_file_b(tmp->next, all_cmd, redi, 0);
	return (tmp);
}

t_builtin	*get_redirection_out(t_builtin *start, int type, void *main_cmd,
	t_command **all_cmd)
{
	t_builtin		*tmp;
	t_raw_builtin	*raw;
	t_redirection	*redi;

	tmp = start;
	if (tmp != 0 && tmp->type == 1 && tmp->raw != 0 && tmp->raw->chara == '>')
	{
		redi = add_redirection(type, 101, main_cmd);
		raw = tmp->raw->next;
		if (raw != 0)
		{
			if (raw->chara == '>')
				redi->type = 102;
			if (raw->chara == '>')
				raw = raw->next;
			if (raw != 0 && (raw->chara == '>' || raw->chara == '<'))
				return (get_redirection_err(type, raw, main_cmd, raw->chara));
			return (get_redirection_3(tmp, all_cmd, raw, redi));
		}
		return (get_redirection_2(tmp, all_cmd, raw, redi));
	}
	return (start);
}

t_builtin	*get_redirection(t_builtin *start, int type, void *main_cmd,
	t_command **all_cmd)
{
	t_builtin		*tmp;

	tmp = start;
	if (tmp != 0 && tmp->type == 1 && tmp->raw != 0)
	{
		if (tmp->raw->chara == '>')
			return (get_redirection_out(start, type, main_cmd, all_cmd));
		else if (tmp->raw->chara == '<')
			return (get_redirection_in(start, type, main_cmd, all_cmd));
	}
	return (start);
}
