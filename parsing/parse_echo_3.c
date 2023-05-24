/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_echo_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 19:18:19 by loculy            #+#    #+#             */
/*   Updated: 2023/05/23 20:13:29 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_echo_error_quote(t_echo *echo, t_builtin *start)
{
	if (echo->value != 0)
		ftm_free(echo->value);
	echo->value = 0;
	echo->printable = 0;
	echo->no_brkln = 1;
	clear_cmd_list(start);
}

void	parse_echo_error(t_echo *echo, int error, char *error_msg)
{
	echo->error = error;
	echo->error_msg = error_msg;
}

int	parse_echo_if(t_builtin *tmp)
{
	if ((tmp->next != 0 && tmp->next->raw != 0
			&& (tmp->next->raw->chara == '>'
				|| tmp->next->raw->chara == '<')))
		return (0);
	if (!((tmp->next == 0 && tmp->type == 0)))
		return (1);
	return (1);
}
