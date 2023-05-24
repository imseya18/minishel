/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:47:24 by loculy            #+#    #+#             */
/*   Updated: 2023/05/23 21:33:16 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_exit	*add_exit(int type)
{
	t_exit			*cmdexit;

	cmdexit = ftm_malloc(sizeof(t_exit));
	if (!cmdexit)
		return (0);
	cmdexit->type = type;
	cmdexit->code = NULL;
	cmdexit->printable = 0;
	cmdexit->error = 0;
	cmdexit->error_msg = NULL;
	cmdexit->stdin = NULL;
	return (cmdexit);
}

void	parse_exit(t_builtin *start, t_command **all_cmd)
{
	t_builtin		*tmp;
	t_raw_builtin	*raw;
	t_exit			*exit;

	exit = add_exit(7);
	ft_cmd_add_back(all_cmd, ft_cmdnew(exit, 7));
	tmp = parse_skip_one(parse_skip_one(parse_skip_space(start)));
	tmp = get_redirection_auto(tmp, 7, exit, all_cmd);
	while (tmp)
	{
		if (!tmp || tmp->type == 0)
		{
			parse_exit_error(exit, 1, ft_strdup_(" exit: too many arguments"));
			return (clear_cmd_list(tmp));
		}
		raw = tmp->raw;
		if (tmp->type == -1)
			return (parse_exit_error_quote(exit, tmp));
		while (raw != 0)
		{
			exit->code = ft_strjoin_char(exit->code, raw->chara);
			raw = raw->next;
		}
		tmp = tmp->next;
	}
}
