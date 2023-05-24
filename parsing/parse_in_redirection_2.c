/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_in_redirection_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:25:17 by loculy            #+#    #+#             */
/*   Updated: 2023/05/19 13:52:01 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_out_parse(char *line)
{
	if (!line)
		return (0);
	return (ft_strdup(""));
}

char	*parse_line(char *line)
{
	char			*out;
	t_builtin		*head_bltn;
	t_builtin		*tmp;
	t_raw_builtin	*raw;

	head_bltn = 0;
	out = get_out_parse(line);
	ft_builtin_line(line, &head_bltn, 0);
	parse_var(&head_bltn, get_main(0));
	tmp = head_bltn;
	while (tmp != 0)
	{
		raw = tmp->raw;
		out = get_quote(out, tmp->type);
		while (raw != 0)
		{
			out = ft_strjoin_char(out, raw->chara);
			raw = raw->next;
		}
		out = get_quote(out, tmp->type);
		tmp = tmp->next;
	}
	ftm_free(line);
	return (out);
}

char	*get_redirection_by_sep(char *separator)
{
	char	*out;
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		error_msg_exit("Error: failed to open pipe.");
	pid = fork();
	out = red_by_sep(separator, fd, pid);
	return (out);
}

t_builtin	*get_redirection_in_sep(t_builtin *start, t_command **all_cmd,
	t_redirection *redi)
{
	t_builtin		*tmp;
	t_raw_builtin	*raw;

	if (!start)
		return (start);
	tmp = parse_skip_space(start->next);
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
	redi->file_name = get_redirection_by_sep(redi->file_name);
	ft_cmd_add_back(all_cmd, ft_cmdnew(redi, redi->type));
	set_stdin(redi->value, redi, redi->value_type);
	if (tmp != 0)
		tmp = tmp->next;
	return (parse_skip_space(tmp));
}

t_builtin	*get_redirection_in_separator(t_builtin *start, t_command **all_cmd,
	t_redirection *redi)
{
	t_builtin		*tmp;
	t_raw_builtin	*raw;

	tmp = start;
	if (!tmp)
		return (tmp);
	raw = tmp->raw;
	if (raw != 0 && raw->next != 0)
		raw = raw->next->next;
	if (!raw)
		return (get_redirection_in_sep(tmp->next, all_cmd, redi));
	while (raw != 0)
	{
		redi->file_name = ft_strjoin_char(redi->file_name, raw->chara);
		raw = raw->next;
	}
	tmp = get_redirection_in_sep(tmp, all_cmd, redi);
	return (tmp);
}
