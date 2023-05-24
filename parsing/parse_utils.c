/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:56:27 by loculy            #+#    #+#             */
/*   Updated: 2023/05/11 11:08:56 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command	*ft_cmdnew(void	*cmd, int type)
{
	t_command			*cmd_link;

	cmd_link = ftm_malloc(sizeof(t_command));
	if (!cmd_link)
		return (0);
	cmd_link->type = type;
	cmd_link->cmd = cmd;
	cmd_link->next = NULL;
	return (cmd_link);
}

void	ft_cmd_add_back(t_command **lst, t_command *new)
{
	t_command	*act;

	if ((*lst) == 0)
	{
		*lst = new;
		return ;
	}
	act = *lst;
	while (act->next != NULL)
		act = act->next;
	act->next = new;
}
