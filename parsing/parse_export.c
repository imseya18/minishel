/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 20:58:21 by loculy            #+#    #+#             */
/*   Updated: 2023/05/23 21:07:52 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_export	*add_export(int type)
{
	t_export			*cmdexport;

	cmdexport = ftm_malloc(sizeof(t_export));
	if (!cmdexport)
		return (0);
	cmdexport->type = type;
	cmdexport->name = NULL;
	cmdexport->content = NULL;
	cmdexport->egal = 0;
	cmdexport->envable = 0;
	cmdexport->error = 0;
	cmdexport->error_msg = NULL;
	cmdexport->stdin = NULL;
	return (cmdexport);
}

void	parse_export_egal(t_export *export, t_raw_builtin **raw,
	t_builtin **tmp)
{
	if ((*raw)->chara == '+')
	{
		if ((*raw)->next != 0)
		{
			(*raw) = (*raw)->next;
			if ((*raw)->chara == '=')
				export->egal = 2;
			(*raw) = (*raw)->next;
		}
		else
		{
			(*tmp) = (*tmp)->next;
			if (!(*tmp))
				return ;
			(*raw) = (*tmp)->raw;
			if ((*raw)->chara == '=')
				export->egal = 2;
			(*raw) = (*raw)->next;
		}
	}
	else if ((*raw)->chara == '=')
	{
		export->egal = 1;
		(*raw) = (*raw)->next;
	}
}

t_raw_builtin	*parse_export_fill(t_export *export, t_raw_builtin *raw)
{
	if (!raw)
		return (raw);
	if (export->egal == 0)
		export->name = ft_strjoin_char(export->name, raw->chara);
	else
		export->content = ft_strjoin_char(export->content, raw->chara);
	return (raw->next);
}

void	parse_export_cmd(t_builtin *start, t_command **all_cmd)
{
	t_builtin		*tmp;
	t_raw_builtin	*raw;
	t_export		*export;

	export = add_export(4);
	ft_cmd_add_back(all_cmd, ft_cmdnew(export, 4));
	tmp = parse_skip_space(start);
	tmp = get_redirection_auto(tmp, 4, export, all_cmd);
	while (tmp)
	{
		if (tmp->type == 0)
			return (parse_export_cmd(tmp->next, all_cmd));
		raw = tmp->raw;
		if (tmp->type == -1)
			return (parse_export_error_quote(export, start));
		while (raw != 0)
		{
			parse_export_egal(export, &raw, &tmp);
			raw = parse_export_fill(export, raw);
		}
		tmp = tmp->next;
	}
}

void	parse_export(t_builtin *start, t_command **all_cmd)
{
	t_builtin		*tmp;
	t_raw_builtin	*raw;
	t_export		*export;

	tmp = parse_skip_one(parse_skip_one(parse_skip_space(start)));
	if (!tmp)
	{
		export = add_export(4);
		ft_cmd_add_back(all_cmd, ft_cmdnew(export, 4));
		export->envable = 1;
		return ;
	}
	raw = tmp->raw;
	if (!raw)
	{
		export = add_export(4);
		ft_cmd_add_back(all_cmd, ft_cmdnew(export, 4));
		export->envable = 1;
		return ;
	}
	parse_export_cmd(tmp, all_cmd);
	clear_cmd_list(start);
}
