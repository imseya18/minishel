/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:10:01 by loculy            #+#    #+#             */
/*   Updated: 2023/05/24 12:40:19 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_echo	*add_echo(int type)
{
	t_echo			*cmdecho;

	cmdecho = ftm_malloc(sizeof(t_echo));
	if (!cmdecho)
		return (0);
	cmdecho->type = type;
	cmdecho->no_brkln = 0;
	cmdecho->value = NULL;
	cmdecho->printable = 1;
	cmdecho->error = 0;
	cmdecho->error_msg = NULL;
	cmdecho->stdin = NULL;
	return (cmdecho);
}

t_builtin	*parse_echo_init(t_builtin *start, t_command **all_cmd,
	t_echo *echo)
{
	t_builtin		*tmp;

	tmp = parse_skip_one(parse_skip_one(parse_skip_space(start)));
	tmp = get_redirection(tmp, 1, echo, all_cmd);
	tmp = get_echo_return_line(tmp, &(echo->no_brkln));
	return (tmp);
}

void	parse_echo(t_builtin *start, t_command **all_cmd)
{
	t_builtin		*tmp;
	t_raw_builtin	*raw;
	t_echo			*echo;

	echo = add_echo(1);
	ft_cmd_add_back(all_cmd, ft_cmdnew(echo, 1));
	tmp = parse_echo_init(start, all_cmd, echo);
	start = get_redirection_auto(tmp, 1, echo, all_cmd);
	tmp = start;
	if (!tmp)
		return (clear_cmd_list(start));
	while (tmp)
	{
		raw = tmp->raw;
		if (tmp->type == -1)
			return (parse_echo_error_quote(echo, start));
		while (raw != 0)
		{
			if (!((tmp->next == 0 && tmp->type == 0)))
				echo->value = ft_strjoin_char(echo->value, raw->chara);
			raw = raw->next;
		}
		tmp = tmp->next;
	}
	clear_cmd_list(start);
}
