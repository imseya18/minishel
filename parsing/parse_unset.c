/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:13:21 by loculy            #+#    #+#             */
/*   Updated: 2023/05/23 21:51:19 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_unset	*add_unset(int type)
{
	t_unset			*cmdunset;

	cmdunset = ftm_malloc(sizeof(t_unset));
	if (!cmdunset)
		return (0);
	cmdunset->type = type;
	cmdunset->name = NULL;
	cmdunset->printable = 0;
	cmdunset->error = 0;
	cmdunset->error_msg = NULL;
	cmdunset->stdin = NULL;
	return (cmdunset);
}

void	parse_unset_cmd(t_builtin *start, t_command **all_cmd)
{
	t_builtin		*tmp;
	t_raw_builtin	*raw;
	t_unset			*unset;

	unset = add_unset(5);
	ft_cmd_add_back(all_cmd, ft_cmdnew(unset, 5));
	tmp = parse_skip_space(start);
	start = get_redirection_auto(tmp, 5, unset, all_cmd);
	tmp = start;
	while (tmp)
	{
		if (tmp->type == 0)
			return (parse_unset_cmd(tmp->next, all_cmd));
		raw = tmp->raw;
		if (tmp->type == -1)
			return (parse_unset_error_quote(unset, start));
		while (raw != 0)
		{
			unset->name = ft_strjoin_char(unset->name, raw->chara);
			raw = raw->next;
		}
		tmp = tmp->next;
	}
	clear_cmd_list(start);
}

void	parse_unset(t_builtin *start, t_command **all_cmd)
{
	t_builtin		*tmp;

	tmp = parse_skip_one(parse_skip_one(parse_skip_space(start)));
	parse_unset_cmd(tmp, all_cmd);
}
