/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_auto_redi.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 20:37:08 by loculy            #+#    #+#             */
/*   Updated: 2023/05/23 21:48:41 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_between_redi(t_builtin *start, t_builtin *end)
{
	t_builtin	*tmp;
	t_builtin	*del;

	tmp = start;
	while (tmp && tmp != end)
	{
		del = tmp;
		tmp = tmp->next;
		ftm_free(del);
	}
}

t_builtin	*get_redirection_auto(t_builtin *start, int type, void *main_cmd,
	t_command **all_cmd)
{
	t_builtin	*tmp;
	t_builtin	*last;
	t_builtin	*new;

	tmp = start;
	new = 0;
	while (tmp)
	{
		last = tmp;
		tmp = get_redirection(last, type, main_cmd, all_cmd);
		if (last == tmp)
		{
			tmp = tmp->next;
			last->next = 0;
			ft_bltnadd_back(&new, last);
		}
		else
			free_between_redi(last, tmp);
	}
	return (new);
}
