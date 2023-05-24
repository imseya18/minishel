/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:40:37 by loculy            #+#    #+#             */
/*   Updated: 2023/05/23 21:32:57 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cd	*add_cd(int type)
{
	t_cd			*cmdcd;

	cmdcd = ftm_malloc(sizeof(t_cd));
	if (!cmdcd)
		return (0);
	cmdcd->type = type;
	cmdcd->path = NULL;
	cmdcd->printable = 0;
	cmdcd->error = 0;
	cmdcd->error_msg = NULL;
	cmdcd->stdin = NULL;
	return (cmdcd);
}

void	parse_cd(t_builtin *start, t_command **all_cmd, t_minishell *main)
{
	t_builtin		*tmp;
	t_raw_builtin	*raw;
	t_cd			*cd;

	cd = add_cd(2);
	ft_cmd_add_back(all_cmd, ft_cmdnew(cd, 2));
	tmp = parse_skip_one(parse_skip_one(parse_skip_space(start)));
	tmp = get_redirection_auto(tmp, 2, cd, all_cmd);
	while (tmp)
	{
		if (!tmp || tmp->type == 0)
			return (clear_cmd_list(tmp));
		raw = tmp->raw;
		if (tmp->type == -1)
			return (parse_cd_error_quote(cd, tmp));
		while (raw != 0)
		{
			if (tmp->type == 1 && raw->chara == '~' && cd->path == 0)
				cd->path = ft_strdup_(ft_get_env(&main->var_env, "HOME"));
			else
				cd->path = ft_strjoin_char(cd->path, raw->chara);
			raw = raw->next;
		}
		tmp = tmp->next;
	}
}
