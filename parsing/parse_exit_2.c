/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exit_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:11:24 by loculy            #+#    #+#             */
/*   Updated: 2023/05/12 13:14:36 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_exit_error_quote(t_exit *exit, t_builtin *start)
{
	if (exit->code != 0)
		ftm_free(exit->code);
	exit->code = 0;
	exit->printable = 0;
	clear_cmd_list(start);
}

void	parse_exit_error(t_exit *exit, int error, char *error_msg)
{
	exit->error = error;
	exit->error_msg = error_msg;
}
