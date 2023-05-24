/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:18:13 by loculy            #+#    #+#             */
/*   Updated: 2023/05/23 16:31:28 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_nbr_of_pipe(t_command **lst)
{
	t_command	*tmp;
	int			nbr;

	nbr = 0;
	if (!*lst)
		return (0);
	tmp = *lst;
	while (tmp != NULL)
	{
		if (tmp->type == 100)
			nbr++;
		tmp = tmp->next;
	}
	return (nbr);
}
