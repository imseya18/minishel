/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_none.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:17:37 by loculy            #+#    #+#             */
/*   Updated: 2023/05/23 21:34:35 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_none	*add_none(int type)
{
	t_none			*cmdnone;

	cmdnone = ftm_malloc(sizeof(t_none));
	if (!cmdnone)
		return (0);
	cmdnone->type = type;
	cmdnone->printable = 0;
	cmdnone->error = 0;
	cmdnone->error_msg = NULL;
	cmdnone->stdin = NULL;
	return (cmdnone);
}

void	parse_none(t_builtin *start, t_command **all_cmd, int type)
{
	t_builtin		*tmp;
	t_none			*none;

	none = add_none(type);
	ft_cmd_add_back(all_cmd, ft_cmdnew(none, type));
	tmp = parse_skip_one(parse_skip_one(parse_skip_space(start)));
	start = get_redirection_auto(tmp, type, none, all_cmd);
	tmp = start;
	while (tmp)
	{
		if (tmp->type == -1)
			return (parse_none_error_quote(none, start));
		tmp = tmp->next;
	}
	clear_cmd_list(start);
}

void	parse_none_for_err(t_command **all_cmd)
{
	t_none			*none;

	none = add_none(202);
	ft_cmd_add_back(all_cmd, ft_cmdnew(none, 202));
	none->error_msg = ft_strdup_("syntax error near unexpected token `|'");
}
