/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 16:47:20 by loculy            #+#    #+#             */
/*   Updated: 2023/05/24 13:49:36 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_cmd_type_value(t_builtin *tmp, char *out)
{
	t_raw_builtin	*raw;
	int				i;

	i = 0;
	while (tmp != 0 && tmp->type != 0)
	{
		raw = tmp->raw;
		while (raw != 0)
		{
			out[i++] = raw->chara;
			raw = raw->next;
		}
		tmp = tmp->next;
	}
	return (out);
}

char	*get_cmd_type(t_builtin *tmp)
{
	t_builtin		*start;
	t_raw_builtin	*raw;
	int				size;
	char			*out;

	size = 0;
	start = tmp;
	while (tmp != 0 && tmp->type != 0)
	{
		raw = tmp->raw;
		while (raw != 0)
		{
			size++;
			raw = raw->next;
		}
		tmp = tmp->next;
	}
	out = ftm_malloc(sizeof(char) * (size + 1));
	out[size] = 0;
	return (get_cmd_type_value(start, out));
}

void	get_exist_cmd(t_builtin *start, char *cmd_name, t_command **all_cmd,
	t_minishell *main)
{
	if (ft_strcmp(cmd_name, "echo") == 0)
		parse_echo(start, all_cmd);
	else if (ft_strcmp(cmd_name, "cd") == 0)
		parse_cd(start, all_cmd, main);
	else if (ft_strcmp(cmd_name, "export") == 0)
		parse_export(start, all_cmd);
	else if (ft_strcmp(cmd_name, "pwd") == 0)
		parse_none(start, all_cmd, 3);
	else if (ft_strcmp(cmd_name, "env") == 0)
		parse_none(start, all_cmd, 6);
	else if (ft_strcmp(cmd_name, "unset") == 0)
		parse_unset(start, all_cmd);
	else if (ft_strcmp(cmd_name, "exit") == 0)
		parse_exit(start, all_cmd);
	else if (ft_strcmp(cmd_name, "") == 0)
		parse_none_for_err(all_cmd);
	else
		parse_exec(start, all_cmd);
	if (!cmd_name)
		ftm_free(cmd_name);
}

int	is_skipable(t_builtin *start)
{
	t_builtin		*tmp;
	t_raw_builtin	*raw;

	tmp = start;
	if (!tmp)
		return (0);
	if (tmp->type == 1)
	{
		raw = tmp->raw;
		while (raw)
		{
			if (raw->chara != 0)
				return (0);
			raw = raw->next;
		}
		return (1);
	}
	return (0);
}

void	get_cmds(t_parsed_cmd **cmd, t_command **all_cmd, t_minishell *main)
{
	t_parsed_cmd	*act;
	t_builtin		*tmp;
	t_builtin		*start;

	act = *cmd;
	while (act)
	{
		if (act->type == 1)
		{
			tmp = act->cmd;
			start = tmp;
			while (tmp != 0 && (tmp->type == 0 || is_skipable(tmp) == 1))
				tmp = tmp->next;
			get_exist_cmd(tmp, get_cmd_type(tmp), all_cmd, main);
		}
		if (act->type == 10)
			ft_cmd_add_back(all_cmd, ft_cmdnew(add_pipe(), 100));
		act = act->next;
	}
}
