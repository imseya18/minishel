/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loculy <loculy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:47:38 by loculy            #+#    #+#             */
/*   Updated: 2023/05/02 19:08:39 by loculy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_exec_error_quote(t_exec *exec, t_builtin *start)
{
	exec->printable = 0;
	exec->error = 1;
	clear_cmd_list(start);
}

void	parse_exec_error(t_exec *exec, int error, char *error_msg)
{
	exec->error = error;
	exec->error_msg = error_msg;
}

char	*get_exec_argum_str(t_builtin *tmp, char *str, t_exec *exec)
{
	if (!tmp || (tmp->type == 0 && ft_strlen_(str) > 0))
	{
		exec_add_flags(exec, str);
		return (0);
	}
	return (str);
}
